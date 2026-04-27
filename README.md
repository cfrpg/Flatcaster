# Flatcaster

纯 PCB 实现的电容触摸吉他项目。

基于 AT32F435 主控，板载 AT-Link 下载器。采用 MAX98357A 功放输出，支持自校准电容矩阵触摸，可独立控制 6 根琴弦的拨动和 6 个品位，实现完整的弹奏体验。音色采用 Karplus-Strong 物理建模（采样音源 TBD）。包含网页上位机程序。

演示视频：[Bilibili](https://www.bilibili.com/video/BV1TAoMBCENc)

## 特性

- 纯 PCB 吉他结构
- AT32F435 主控 + 板载 AT-Link 下载器
- MAX98357A 功放输出
- 自校准电容矩阵触摸（6 根弦 + 6 个品位）
- Karplus-Strong 物理建模音色
- 网页上位机程序

## 项目结构

```bash
Flatcaster/
├── doc/          # 文档与仿真文件
├── pcb/          # Altium 硬件设计
├── src/
│   ├── v0.1/     # AT32F435 固件源码
│   └── touch.html # 网页上位机
└── ...
