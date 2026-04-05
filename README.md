# 8x8x8 LED Cube Project

## Overview ![Overview](https://img.shields.io/badge/Project-Overview-blue?style=flat-square&logo=info&logoColor=white)
Repo นี้เป็นโปรเจกวิชา Circuit & Electronic ของผมตอนเรียนอยู่ KMITL โดยโปรเจคนี้เป็นหัวข้อที่ Assign มาจากอาจารย์อีกที โจทย์คือทำ Led Cube ขนาดใดก็ได้โดยจะนำโปรเจคนี้ไปให้เด็กพิการได้ใช้เป็นสื่อในการเรียนรู้ ตัวของโปรเจคเริ่มจากการเลือกใช้ โปรแกรมออกแบบและตัวหน้าที่ต่างๆ เราจะออกแบบ Model ของกล่องที่ใช้เป็นฐานเก็บวงจรและเป็น Base ให้กับตัว Led Cube ด้วย Solid Work 2023 แล้วนำตัวโมเดล Cad ไปปริ้นด้วย 3D Printer อีกที ตัววงจรจะออกแบบด้วย EasyEDA โดยใช้บอร์ด Control เป็น Arduino UNO R4 WIFI แล้วสื่อสารกับตัว Shift Register แบบ Serial in Parallel Out (SIPO) ด้วย Protocol SPI แล้วใช้ Transistor BD241C เป็น Low Side Switch ในการเปิดปิดและรับโหลดของหลอดไฟทั้ง Layer เนื่องจากกระแสในวงจรนั้นสูงมาก จากหลอดไฟ 20mA ทั้งเลเยอร์หรือก็คือ 64 หลอด 64 X 0.02 mA = 1.28A ซึ้งเสเปกโดยทั้วไปอาจจะใช้ขับหลอดไฟภายในเลเยอร์ไม่ได้ในส่วนของโปรแกรมจะสั่ง Input จาก 4X4 KeyPad แล้วใช้เป็น Logic Decision ในการเล่น Animation โดยตัวโค้ดในการออกแบบ Animation จะใช้จินตนาการว่า Led Cube คือการ Integrate พื้นที่ในแคลคูลัสแบบ Discrete 8X8X8 หรือแยก Position เป็น จุดออกมาจากการอินทีเกรตแล้วเขียนกราฟที่มี Animation ลงไปในสมการให้ตัว โหนดแต่ละโหนดเล่นตามสมการจึงเป็นสาเหตุว่าใน Code เป็นสมการแทบจะทั้งหมด

![LED Cube Animation](./Docs/Project_media/Led_Cube_Gif.gif)

## Tech Stack ![TechStack](https://img.shields.io/badge/System-Architecture_&_Tools-8E44AD?style=flat-square&logo=cpu&logoColor=white)
- $\color{cyan}{\textbf{Hardware :}}$ Arduino UNO R4 WIFI, 74HC595 ![Arduino](https://img.shields.io/badge/MCU-Arduino_UNO_R4_WIFI-00979D?logo=arduino&logoColor=white)
- $\color{orange}{\textbf{Firmware :}}$ C++ (Arduino Framework) ![Language](https://img.shields.io/badge/Language-C++-00599C?logo=c%2B%2B)
- $\color{purple}{\textbf{Design :}}$ Solid Work 2023, EasyEDA ![EasyEDA](https://img.shields.io/badge/Circuit-EasyEDA-0052CC)

## Concept ![Concept](https://img.shields.io/badge/Driving-Multiplexing-red?style=flat-square)
เราใช้การควบคุมแบบ $8 \times 8 \times 8$ โดยแบ่งเป็น:
- $\color{green}{\textbf{Columns : }}$ 64 จุด ควบคุมผ่าน 8x Shift Registers
- $\color{green}{\textbf{Layers : }}$ 8 ชั้น ควบคุมผ่าน Transistor Darlington Array

## Build Process ![Process](https://img.shields.io/badge/Process-Build_&_Assembly-E67E22?style=flat-square&logo=tools&logoColor=white)
| Building the Jig | Soldering Layers | Final Assembly |
| :---: | :---: | :---: |
| <img src="./Docs/Project_Image/74B12784-0B87-41C8-9E61-A98689FC6D83.jpg" height="250" alt="Building the Jig"> | <img src="./Docs/Project_Image/IMG_20250311_224342.jpg" height="250" alt="Soldering Layers"> | <img src="./Docs/Project_Image/1775366971204.jpg" height="250" alt="Final Assembly"> |

## Contributors ![Contributors](https://img.shields.io/badge/Group-Contributors-2ECC71?style=flat-square&logo=github&logoColor=white)
- $\color{red}{\textbf{Panya Triprom}}$ ([@KENASTES](https://github.com/KENASTES))
- $\color{red}{\textbf{Rathiphat Buakaew}}$ ([@ratiphat2548](https://github.com/ratiphat2548))
- $\color{red}{\textbf{Ploynumthong Chaiyotha}}$ ([@Ploynumthong](https://github.com/Ploynumthong))

---
*Created for Educational Purpose @KMITL*