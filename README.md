# 8x8x8 LED Cube Project
> A 3D Light Show powered by Arduino and sheer willpower.

![LED Cube Animation](https://link-to-your-gif.gif)

## Overview
โปรเจกต์นี้เป็นส่วนหนึ่งของวิชา Circuit @KMITL โดยมีจุดประสงค์เพื่อศึกษาการควบคุม Digital Output จำนวนมากด้วย Shift Registers

## Tech Stack
- **Hardware:** Arduino Nano, 74HC595
- **Firmware:** C++ (Arduino Framework)
- **Design:** EasyEDA

## System Architecture
เราใช้การควบคุมแบบ $8 \times 8 \times 8$ โดยแบ่งเป็น:
- **Columns:** 64 จุด (ควบคุมผ่าน 8x Shift Registers)
- **Layers:** 8 ชั้น (ควบคุมผ่าน Darlington Array)

## Build Process
| Building the Jig | Soldering Layers | Final Assembly |
| :---: | :---: | :---: |
| ![Pic1](url) | ![Pic2](url) | ![Pic3](url) |

## Contributors
- **Panya Triprom** (@KENASTES) - Firmware, Circuit Design, Testing, Soldering
- **Rathiphat Buakaew** (@ratiphat2548) - Hardware Assembly & Soldering
- **Ploynumthong Chaiyotha** (@Ploynumthong) - List of Component, Order the Component