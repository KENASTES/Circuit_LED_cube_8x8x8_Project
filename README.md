# 8x8x8 LED Cube Project
> A 3D Light Show powered by Arduino and sheer willpower.

![LED Cube Animation](./Project_media/Led_Cube_Gif.gif)

## Overview
Repo นี้เป็นโปรเจกวิชา Circuit & Electronic ของผมตอนเรียนอยู่ KMITL โดยโปรเจคนี้เป็นหัวข้อที่ Assign มาจากอาจารย์อีกที โจทย์คือทำ Led Cube ขนาดใดก็ได้โดยจะนำโปรเจคนี้ไปให้เด็กพิการได้ใช้เป็นสื่อในการเรียนรู้ ตัวของโปรเจคเริ่มจากการเลือกใช้ โปรแกรมออกแบบและตัวหน้าที่ต่างๆ เราจะออกแบบ Model ของกล่องที่ใช้เป็นฐานเก็บวงจรและเป็น Base ให้กับตัว Led Cube ด้วย Solid Work 2023 แล้วนำตัวโมเดล Cad ไปปริ้นด้วย 3D Printer อีกที ตัววงจรจะออกแบบด้วย EasyEDA โดยใช้บอร์ด Control เป็น Arduino UNO R4 WIFI แล้วสื่อสารกับตัว Shift Register แบบ Serial in Parallel Out (SIPO) ด้วย Protocol SPI แล้วใช้ Transistor BD241C เป็น Low Side Switch ในการเปิดปิดและรับโหลดของหลอดไฟทั้ง Layer เนื่องจากกระแสในวงจรนั้นสูงมาก จากหลอดไฟ 20mA ทั้งเลเยอร์หรือก็คือ 64 หลอด 64 X 0.02 mA = 1.28A ซึ้งเสเปกโดยทั้วไปอาจจะใช้ขับหลอดไฟภายในเลเยอร์ไม่ได้ในส่วนของโปรแกรมจะสั่ง Input จาก 4X4 KeyPad แล้วใช้เป็น Logic Decision ในการเล่น Animation โดยตัวโค้ดในการออกแบบ Animation จะใช้จินตนาการว่า Led Cube คือการ Integrate พื้นที่ในแคลคูลัสแบบ Discrete 8X8X8 หรือแยก Position เป็น จุดออกมาจากการอินทีเกรตแล้วเขียนกราฟที่มี Animation ลงไปในสมการให้ตัว โหนดแต่ละโหนดเล่นตามสมการจึงเป็นสาเหตุว่าใน Code เป็นสมการแทบจะทั้งหมด

## Tech Stack
- **Hardware:** Arduino UNO R4 WIFI, 74HC595
- **Firmware:** C++ (Arduino Framework)
- **Design:** EasyEDA

## System Architecture
เราใช้การควบคุมแบบ $8 \times 8 \times 8$ โดยแบ่งเป็น:
- **Columns:** 64 จุด (ควบคุมผ่าน 8x Shift Registers)
- **Layers:** 8 ชั้น (ควบคุมผ่าน Darlington Array)

## Build Process
| Building the Jig | Soldering Layers | Final Assembly |
| :---: | :---: | :---: |
| ![Pic1](./Docs/Project_Image/74B12784-0B87-41C8-9E61-A98689FC6D83.jpg) | ![Pic2](./Docs/Project_Image/IMG_20250311_224342.jpg) | ![Pic3](./Docs/Project_Image/1775366971204.jpg) |

## Contributors
- **Panya Triprom** (@KENASTES)
- **Rathiphat Buakaew** (@ratiphat2548)
- **Ploynumthong Chaiyotha** (@Ploynumthong)