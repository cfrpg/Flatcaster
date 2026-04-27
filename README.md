# Flatcaster

纯 PCB 实现的电容触摸吉他项目。

基于 AT32F435 主控，板载 AT-Link 下载器。采用 MAX98357A 功放输出，支持自校准电容矩阵触摸，可独立控制 6 根琴弦的拨动和 6 个品位，实现完整的弹奏体验。音色采用 Karplus-Strong 物理建模和 [Unreal Instruments](https://sfzinstruments.github.io/guitars/standard_guitar/) 的采样音源。包含网页上位机程序。

演示视频：[Bilibili](https://www.bilibili.com/video/BV1TAoMBCENc)

## 特性

- 纯 PCB 吉他结构
- AT32F435 主控 + 板载 AT-Link 下载器
- MAX98357A 功放输出
- 自校准电容矩阵触摸（6 根弦 + 6 个品位）
- Karplus-Strong 物理建模音色
- Unreal Instruments - Standard Guitar 音源
- 网页上位机程序

## 操作
### 演奏
打开开关，使用电位器调节音量。左侧6*7触摸区域为品位区，右侧长条触摸为拨弦区。

### 改变音色
按**A**键切换音色，LED蓝色闪烁为K-S音色，绿色闪烁为Unreal Instruments采样音源。

### 调整变调夹和移调
按下**B**键并保持按住开始调整。

在品位区选择需要移动的半音数，**6弦1品**为移动**0个半音**，每增加一品**半音数+1**，每向上一条弦**半音数+6**。

按住的品位后，**拨动1弦**设置为移调数，**拨动6弦**设置为变调夹位置

**拨动3弦或4弦**恢复初始设置。

松开**B**键使设置生效。

**eg：** 设置移调为2，变调夹为3，此时空弦变为原本的3品，1品变为原本的6品（1品+变调夹3+移调2）。

### 使用网页端上位机
下载src/Flatcaster.html到本地，使用USB线连接计算机，浏览器打开Flatcaster.html，点击连接串口，选择对应的串口连接。
 
## 项目结构

```bash
Flatcaster/
├── doc/                # AT32引脚分配与仿真文件
├── pcb/                # 硬件设计
├── src/
│   ├── v0.1/           # AT32F435 固件源码
│   └── Flatcaster.html # 网页上位机
└── ...
