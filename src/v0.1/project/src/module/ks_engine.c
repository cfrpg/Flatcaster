#include "ks_engine.h"
/**
 * 初始化引擎
 */
void ks_init(KS_Engine *engine, float fs) {
    engine->sample_rate = fs;
    engine->noise_ptr = 0;
    
    for (int i = 0; i < NUM_STRINGS; i++) {
        engine->strings[i].active = false;
        engine->strings[i].ptr = 0;
        engine->strings[i].L = 0;
        memset(engine->strings[i].delay_line, 0, sizeof(float) * MAX_DELAY_LINE_LENGTH);
    }
}

/**
 * 触发弦
 * @param engine 引擎指针
 * @param string_idx 弦索引 (0-5)
 * @param freq 触发频率
 * @param alpha 衰减系数 (例如 0.995)
 * @param factor 滤波因子 (例如 0.5)
 */
void trig_note(KS_Engine *engine, uint8_t string_idx, float freq, float alpha, float factor) {
    if (string_idx >= NUM_STRINGS) return;

    KS_String *s = &engine->strings[string_idx];
    
    // 1. 计算长度 L
    uint32_t L = (uint32_t)(engine->sample_rate / freq + 0.5f);
    if (L > MAX_DELAY_LINE_LENGTH) L = MAX_DELAY_LINE_LENGTH;
    
    s->L = L;
    s->ptr = 0;
    s->alpha = alpha;
    s->filter_factor = factor;
    s->active = true;

    // 2. 从预定义噪声表中拷贝数据 (替代随机数)
    // 每次触发后移动 noise_ptr，确保多弦齐发时音色有细微区别
    for (uint32_t i = 0; i < L; i++) {
        s->delay_line[i] = noise_table[engine->noise_ptr];
        engine->noise_ptr++;
        if (engine->noise_ptr >= noise_table_size) {
            engine->noise_ptr = 0;
        }
    }
}

/**
 * 更新单根弦并返回下一个采样点
 * 这里实现了 MATLAB 逻辑：(val + next_val) * 0.5 * alpha
 * 并加入了可调的 factor 权重
 */
float update_string(KS_String *s) {
    if (!s->active) return 0.0f;

    // 获取当前采样点
    float current_val = s->delay_line[s->ptr];

    // 获取下一个采样点 (用于滤波)
    uint32_t next_idx = s->ptr + 1;
    if (next_idx >= s->L) next_idx = 0;
    float next_val = s->delay_line[next_idx];

    // KS 核心滤波算法
    // 这里的逻辑对应 MATLAB: new_val = (current*f + next*(1-f)) * alpha
    float filtered = (current_val * s->filter_factor + next_val * (1.0f - s->filter_factor));
    float new_val = filtered * s->alpha;

    // 写回缓冲区并移动指针
    s->delay_line[s->ptr] = new_val;
    s->ptr = next_idx;

    return current_val;
}

/**
 * 批量更新单根弦并混音到输出缓冲区
 * @param s 弦状态结构体
 * @param out_buffer 指向 I2S 缓冲区的指针
 * @param num_samples 本次处理的样本数 (e.g., 512)
 */
void batch_update_string(KS_String *s, float *out_buffer, uint32_t num_samples) {
    if (!s->active) return;

    // 局部变量化，方便编译器优化寄存器分配
    float *line = s->delay_line;
    uint32_t ptr = s->ptr;
    uint32_t L = s->L;
    float alpha = s->alpha;
    float f = s->filter_factor;
    float inv_f = 1.0f - f;

    for (uint32_t n = 0; n < num_samples; n++) {
        // 1. 获取当前点
        float current_val = line[ptr];

        // 2. 混音叠加 (直接加到输出缓冲区)
        out_buffer[n] += current_val;

        // 3. 计算下一个位置
        uint32_t next_idx = ptr + 1;
        if (next_idx >= L) next_idx = 0;
        float next_val = line[next_idx];

        // 4. 滤波与写回
        line[ptr] = (current_val * f + next_val * inv_f) * alpha;

        // 5. 移动指针
        ptr = next_idx;
    }

    s->ptr = ptr; // 更新回结构体
}

void stop_string_soft(KS_String *s) {
    // 将衰减系数设为一个非常小的值（如 0.5 或更小）
    // 这样在下一次 block 更新时，能量会呈指数级迅速衰减到 0
    s->alpha *= 0.1f; 
    
    // 注意：不要立即设 active = false，让 update 函数再跑一两个周期
    // 或者在 update 函数中检测如果能量低于某个阈值，再由 update 设置 active = false
}
