#ifndef _KS_ENGINE_H
#define _KS_ENGINE_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

// 假设最低音 E2 (82.4Hz) 在 44.1kHz 下约 535 个采样点
// 预留足够大的空间，或者根据实际需要调整
#define MAX_DELAY_LINE_LENGTH 700 
#define NUM_STRINGS 6

// 引用外部预定义的噪声表
extern const float noise_table[];
extern const uint32_t noise_table_size;

// 单根弦的状态结构体
typedef struct {
    float delay_line[MAX_DELAY_LINE_LENGTH]; // 环形缓冲区
    uint32_t L;              // 弦的物理长度 (采样点数)
    uint32_t ptr;            // 当前读写指针
    float alpha;             // 衰减系数 (Sustain)
    float filter_factor;     // 滤波器权重 (Tone: 0.5 为标准 KS，越偏离 0.5 越沉闷)
    bool active;             // 激活状态
} KS_String;

// 发声引擎总结构体
typedef struct {
    KS_String strings[NUM_STRINGS];
    float sample_rate;
    uint32_t noise_ptr;      // 用于在噪声表中循环取样，保证每根弦触发时的噪声段不同
} KS_Engine;

// 函数声明
void ks_init(KS_Engine *engine, float fs);
void trig_note(KS_Engine *engine, uint8_t string_idx, float freq, float alpha, float factor);
float update_string(KS_String *s);
void batch_update_string(KS_String *s, float *out_buffer, uint32_t num_samples);
void stop_string_soft(KS_String *s);

#endif