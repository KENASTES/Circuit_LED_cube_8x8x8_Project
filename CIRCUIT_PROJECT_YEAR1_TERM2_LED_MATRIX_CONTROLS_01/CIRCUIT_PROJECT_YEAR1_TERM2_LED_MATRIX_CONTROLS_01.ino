////////// INCLUDE BLOCK //////////
#include <LiquidCrystal_I2C.h>
#include <ArduinoMqttClient.h>
#include <DIYables_Keypad.h>
#include <SPI.h>
/////////////////////////////////////

////////// DEFINE VARIBLE //////////
#define XAXIS 1
#define YAXIS 2
#define ZAXIS 0
#define LAYER_COUNT 8

#define POS_X 0
#define POS_Y 1
#define POS_Z 2
#define NEG_X 3
#define NEG_Y 4
#define NEG_Z 5

#define TOTAL_EFFECTS 12
#define CLEAR 49              //1
#define RAIN 50               //2
#define RANDOMBLINK 51        //3
#define FIREWORK 52        //4
#define WOOP_WOOP 53          //5
#define CUBE_JUMP 54          //6
#define WAVE 55               //7
#define RAINDROP 56           //8
#define LIT 57                //9
#define WTF 65          //10
#define SPARKLE 66            //11
#define CROSSEXPANDEFFECT 67  //12
#define EXP 68              //13
#define PLANE 69              //14
#define PULSE 70               //15
#define GROWTH 71                //16

#define RAIN_TIME 260
#define PLANE_BOING_TIME 180
#define SINE_WAVE_TIME 69
#define WOOP_WOOP_TIME 350
#define CUBE_JUMP_TIME 200
#define GLOW_TIME 8
#define BOUNCE_TIME 500
#define ROTATE_TIME 500
#define FIREWORK_TIME 32
#define WAVE_SLIDE_TIME 250
#define EXPLOSION_TIME 600
#define WAVEY_TIME 250
#define PULSE_TIME 1000
#define HEARTBEAT_TIME 690
/////////////////////////////////////

////////// SETTING VARIBLE //////////
// MATRIX FRAME ของ CUBE
const uint8_t numbers[10][8] = {
  {0x3E, 0x51, 0x49, 0x45, 0x3E, 0x00, 0x00, 0x00}, // 0
  {0x00, 0x42, 0x7F, 0x40, 0x00, 0x00, 0x00, 0x00}, // 1
  {0x72, 0x49, 0x49, 0x49, 0x46, 0x00, 0x00, 0x00}, // 2
  {0x22, 0x41, 0x49, 0x49, 0x36, 0x00, 0x00, 0x00}, // 3
  {0x18, 0x14, 0x12, 0x7F, 0x10, 0x00, 0x00, 0x00}, // 4
  {0x27, 0x45, 0x45, 0x45, 0x39, 0x00, 0x00, 0x00}, // 5
  {0x3E, 0x49, 0x49, 0x49, 0x30, 0x00, 0x00, 0x00}, // 6
  {0x03, 0x01, 0x71, 0x09, 0x07, 0x00, 0x00, 0x00}, // 7
  {0x36, 0x49, 0x49, 0x49, 0x36, 0x00, 0x00, 0x00}, // 8
  {0x06, 0x49, 0x49, 0x49, 0x3E, 0x00, 0x00, 0x00}  // 9
};

uint8_t TEST[1][8] = {
  { 0x24, 0x7e, 0xff, 0x7e, 0x3c, 0x18, 0x0, 0 }
};

// กำหนดสถาณะการเล่นปัจจุบัน
uint8_t cube[8][8];
uint8_t Current_State;

// กำหนดจำนวนแถวใน LCD
const int lcdAddress = 0x27;
const int lcdColumns = 16;
const int lcdRows = 2;

// กำหนดแถวที่จะใช้ใน Keypad
const int ROWS_NUM = 4;
const int COLS_NUM = 4;

// กำหนด ปุ่มใน Matrix Keypad
char keys[ROWS_NUM][COLS_NUM] = {
  { '1', '2', '3', '4' },
  { '5', '6', '7', '8' },
  { '9', 'A', 'B', 'C' },
  { 'D', 'E', 'F', 'G' }
};

// ตั้งตัวแปรค่าเวลา
uint16_t timer;
uint64_t randomTimer;
bool loading;

// กำหนด Pin เข้าของแ่ละแถว
byte pin_cols[COLS_NUM] = { 3, 2, 1, 0 };
byte pin_rows[ROWS_NUM] = { 4, 5, 6, 7 };

// ส่ง parameter ไปให้ฟังชั่นใน Library
DIYables_Keypad keypad = DIYables_Keypad(makeKeymap(keys), pin_rows, pin_cols, ROWS_NUM, COLS_NUM);
LiquidCrystal_I2C lcd(lcdAddress, lcdColumns, lcdRows);
/////////////////////////////////////

////////// SETUP FUNCTION //////////
void setup() {
  // ตั้งย่าน Band สั่ญญาณที่จะอ่าน
  Serial.begin(115200);
  // Setting LED CUBE
  loading = true;
  randomTimer = 0;
  Current_State = 0;
  SPI.begin();
  SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));
  randomSeed(analogRead(0));

  // Setup จอ LCD
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
}

////////// LOOP FUNCTION //////////
void loop() {
  unsigned long currentMillis = millis();
  // ให้ตัว Timer นับไปเรื่อยๆ
  randomTimer++;
  char Input_Key = keypad.getKey();
  // จับค่าปุ่มกดที่กดเข้ามา
  if (Input_Key) {
    Serial.println(Input_Key);
    Current_State = Input_Key;
  }

  if (Current_State == 49) {
    clearCube();
  }

  switch (Current_State) {
    case CLEAR: clearALL(); break;
    case RAIN: rain(); break;                            //2
    case RANDOMBLINK: randomBlink(); break;              //3
    case FIREWORK: fireworkEffect(); break;               //4
    case WOOP_WOOP: woopWoop(); break;                   //5
    case CUBE_JUMP: cubeJump(); break;                   //6
    case WAVE: waveyUpDownEffect(); break;                      //7
    case RAINDROP: RainDrop(); break;                    //8
    case LIT: lit(); break;                              //9
    case WTF: heartbeatEffect(); break;              //10
    case SPARKLE: sparkle(); break;                      //11
    case CROSSEXPANDEFFECT: crossExpandEffect(); break;  //12
    case EXP: explosionEffect(); break;                    //13
    case PLANE: planeBoing(); break;                     //14
    case PULSE: pulseEffect(); break;                //15
    case GROWTH: bouncingBallEffect(); break;                    //16
    default: clearCube();
  }
  renderCube();
}

/////////////////////////////////////

////////// CUBE FUNCTION //////////
// Set Array 3 มิติ
void setVoxel(uint8_t x, uint8_t y, uint8_t z) {
  cube[7 - y][7 - z] |= (0x01 << x);
}

// Set Array 3 มิติ
void clearVoxel(uint8_t x, uint8_t y, uint8_t z) {
  cube[7 - y][7 - z] ^= (0x01 << x);
}

// Set Array 3 มิติ
bool getVoxel(uint8_t x, uint8_t y, uint8_t z) {
  return (cube[7 - y][7 - z] & (0x00 << x)) == (0x00 << x);
}

void updateCube() {
  for (int layer = 0; layer < LAYER_COUNT; layer++) {
    SPI.transfer(0x01 << layer);
    for (int row = 0; row < 8; row++) {
      SPI.transfer(cube[layer][row]);
    }
    digitalWrite(10, HIGH);
    delay(10);
  }
}

void waveyUpDownEffect() {
  static uint8_t phase = 0;

  if (loading) {
    clearCube();
    phase = 0;
    loading = false;
  }

  timer++;
  if (timer > WAVEY_TIME) {
    timer = 0;
    clearCube();
    for (uint8_t x = 0; x < 8; x++) {
      for (uint8_t y = 0; y < 8; y++) {
        uint8_t z = 4 + 3 * sin((x + y + phase) * PI / 8);
        setVoxel(x, y, z);
      }
    }

    phase++;
    if (phase >= 16) phase = 0;
  }
}

void randomBlink() {
  for (int i = 0; i < 1; i++) {
    clearCube();
    for (int j = 0; j < 25; j++) {
      int x = random(0, 8);
      int y = random(0, 8);
      int z = random(0, 8);
      cube[z][y] |= (1 << x);
    }
    updateCube();
    delay(10);
  }
}

void sparkle() {
  for (int i = 0; i < 1; i++) {
    clearCube();
    for (int j = 0; j < 3; j++) {
      int x = random(0, 8);
      int y = random(0, 8);
      int z = random(0, 8);
      cube[z][y] |= (1 << x);
    }
    updateCube();
    delay(100);
  }
}

// ขยับ Bit ของ Array 3 มิติ
void shift(uint8_t dir) {

  if (dir == POS_X) {
    for (uint8_t y = 0; y < 8; y++) {
      for (uint8_t z = 0; z < 8; z++) {
        cube[y][z] = cube[y][z] << 1;
      }
    }
  } else if (dir == NEG_X) {
    for (uint8_t y = 0; y < 8; y++) {
      for (uint8_t z = 0; z < 8; z++) {
        cube[y][z] = cube[y][z] >> 1;
      }
    }
  } else if (dir == POS_Y) {
    for (uint8_t y = 1; y < 8; y++) {
      for (uint8_t z = 0; z < 8; z++) {
        cube[y - 1][z] = cube[y][z];
      }
    }
    for (uint8_t i = 0; i < 8; i++) {
      cube[7][i] = 0;
    }
  } else if (dir == NEG_Y) {
    for (uint8_t y = 7; y > 0; y--) {
      for (uint8_t z = 0; z < 8; z++) {
        cube[y][z] = cube[y - 1][z];
      }
    }
    for (uint8_t i = 0; i < 8; i++) {
      cube[0][i] = 0;
    }
  } else if (dir == POS_Z) {
    for (uint8_t y = 0; y < 8; y++) {
      for (uint8_t z = 1; z < 8; z++) {
        cube[y][z - 1] = cube[y][z];
      }
    }
    for (uint8_t i = 0; i < 8; i++) {
      cube[i][7] = 0;
    }
  } else if (dir == NEG_Z) {
    for (uint8_t y = 0; y < 8; y++) {
      for (uint8_t z = 7; z > 0; z--) {
        cube[y][z] = cube[y][z - 1];
      }
    }
    for (uint8_t i = 0; i < 8; i++) {
      cube[i][0] = 0;
    }
  }
}

// Bit สั่งไฟ ON
void lightCube() {
  for (uint8_t i = 0; i < 8; i++) {
    for (uint8_t j = 0; j < 8; j++) {
      cube[i][j] = 0xFF;
    }
  }
}

// Bit สั่งไฟ OFF
void clearCube() {
  for (uint8_t i = 0; i < 8; i++) {
    for (uint8_t j = 0; j < 8; j++) {
      cube[i][j] = 0;
    }
  }
}

// Bit สั่ง 3 มิติ
void drawCube(uint8_t x, uint8_t y, uint8_t z, uint8_t s) {
  for (uint8_t i = 0; i < s; i++) {
    setVoxel(x, y + i, z);
    setVoxel(x + i, y, z);
    setVoxel(x, y, z + i);
    setVoxel(x + s - 1, y + i, z + s - 1);
    setVoxel(x + i, y + s - 1, z + s - 1);
    setVoxel(x + s - 1, y + s - 1, z + i);
    setVoxel(x + s - 1, y + i, z);
    setVoxel(x, y + i, z + s - 1);
    setVoxel(x + i, y + s - 1, z);
    setVoxel(x + i, y, z + s - 1);
    setVoxel(x + s - 1, y, z + i);
    setVoxel(x, y + s - 1, z + i);
  }
}

// Setting แต่ละ Layer
void setPlane(uint8_t axis, uint8_t i) {
  for (uint8_t j = 0; j < 8; j++) {
    for (uint8_t k = 0; k < 8; k++) {
      if (axis == XAXIS) {
        setVoxel(i, j, k);
      } else if (axis == YAXIS) {
        setVoxel(j, i, k);
      } else if (axis == ZAXIS) {
        setVoxel(j, k, i);
      }
    }
  }
}

// รีเซ็ต CUBE ทุกๆ Loop
void renderCube() {
  for (uint8_t i = 0; i < 8; i++) {
    digitalWrite(SS, LOW);
    SPI.transfer(0x01 << i);
    for (uint8_t j = 0; j < 8; j++) {
      SPI.transfer(cube[i][j]);
    }
    digitalWrite(SS, HIGH);
  }
}

// RAIN ANIMATION
void rain() {
  if (loading) {
    clearCube();
    loading = false;
  }
  timer++;
  if (timer > RAIN_TIME) {
    timer = 0;
    shift(NEG_Y);
    uint8_t numDrops = random(0, 5);
    for (uint8_t i = 0; i < numDrops; i++) {
      setVoxel(random(0, 8), 7, random(0, 8));
    }
  }
}

void RainDrop() {
  for (int i = 0; i < 1; i++) {
    clearCube();
    for (int j = 0; j < 1; j++) {
      int x = random(0, 8);
      int y = random(0, 8);
      for (int z = 7; z >= 0; z--) {
        cube[7 - z][y] |= (1 << x);
        updateCube();
        delay(2);
        cube[7 - z][y] &= ~(1 << x);
      }
    }
  }
}

// SENDVOXELS VARIBLES
uint8_t selX = 0;
uint8_t selY = 0;
uint8_t selZ = 0;
uint8_t sendDirection = 0;
bool sending = false;

void fireworkEffect() {
  if (loading) {
    clearCube();
    loading = false;
  }

  timer++;
  if (timer > FIREWORK_TIME) {
    timer = 0;
    clearCube();

    uint8_t cx = 4, cy = 4, cz = 4;
    for (uint8_t i = 0; i < 8; i++) {
      int dx = random(-3, 4);
      int dy = random(-3, 4);
      int dz = random(-3, 4);
      if (cx + dx < 8 && cy + dy < 8 && cz + dz < 8) {
        setVoxel(cx + dx, cy + dy, cz + dz);
      }
    }

    // เพิ่มการกระจายเหมือนระเบิดดอกไม้ไฟ
    for (uint8_t i = 0; i < 10; i++) {
      int dx = random(-3, 4);
      int dy = random(-3, 4);
      int dz = random(-3, 4);
      setVoxel(cx + dx, cy + dy, cz + dz);
    }
  }
}

// WOOPWOOP VARIBLE
uint8_t cubeSize = 0;
bool cubeExpanding = true;

// WOOPWOOP ANIMATION
void woopWoop() {
  if (loading) {
    clearCube();
    cubeSize = 2;
    cubeExpanding = true;
    loading = false;
  }

  timer++;
  if (timer > WOOP_WOOP_TIME) {
    timer = 0;
    if (cubeExpanding) {
      cubeSize += 2;
      if (cubeSize == 8) {
        cubeExpanding = false;
      }
    } else {
      cubeSize -= 2;
      if (cubeSize == 2) {
        cubeExpanding = true;
      }
    }
    clearCube();
    drawCube(4 - cubeSize / 2, 4 - cubeSize / 2, 4 - cubeSize / 2, cubeSize);
  }
}

// CUBEJUMP VARIBLE
uint8_t xPos;
uint8_t yPos;
uint8_t zPos;

// CUBEJUMP ANIMATION
void cubeJump() {
  if (loading) {
    clearCube();
    xPos = random(0, 2) * 7;
    yPos = random(0, 2) * 7;
    zPos = random(0, 2) * 7;
    cubeSize = 8;
    cubeExpanding = false;
    loading = false;
  }

  timer++;
  if (timer > CUBE_JUMP_TIME) {
    timer = 0;
    clearCube();
    if (xPos == 0 && yPos == 0 && zPos == 0) {
      drawCube(xPos, yPos, zPos, cubeSize);
    } else if (xPos == 7 && yPos == 7 && zPos == 7) {
      drawCube(xPos + 1 - cubeSize, yPos + 1 - cubeSize, zPos + 1 - cubeSize, cubeSize);
    } else if (xPos == 7 && yPos == 0 && zPos == 0) {
      drawCube(xPos + 1 - cubeSize, yPos, zPos, cubeSize);
    } else if (xPos == 0 && yPos == 7 && zPos == 0) {
      drawCube(xPos, yPos + 1 - cubeSize, zPos, cubeSize);
    } else if (xPos == 0 && yPos == 0 && zPos == 7) {
      drawCube(xPos, yPos, zPos + 1 - cubeSize, cubeSize);
    } else if (xPos == 7 && yPos == 7 && zPos == 0) {
      drawCube(xPos + 1 - cubeSize, yPos + 1 - cubeSize, zPos, cubeSize);
    } else if (xPos == 0 && yPos == 7 && zPos == 7) {
      drawCube(xPos, yPos + 1 - cubeSize, zPos + 1 - cubeSize, cubeSize);
    } else if (xPos == 7 && yPos == 0 && zPos == 7) {
      drawCube(xPos + 1 - cubeSize, yPos, zPos + 1 - cubeSize, cubeSize);
    }
    if (cubeExpanding) {
      cubeSize++;
      if (cubeSize == 8) {
        cubeExpanding = false;
        xPos = random(0, 2) * 7;
        yPos = random(0, 2) * 7;
        zPos = random(0, 2) * 7;
      }
    } else {
      cubeSize--;
      if (cubeSize == 1) {
        cubeExpanding = true;
      }
    }
  }
}

// LIT ANIMATION
void lit() {
  clearCube();
  for (uint8_t i = 0; i < 8; i++) {
    for (uint8_t j = 0; j < 8; j++) {
      cube[i][j] = 0xFF;
    }
  }
}

void crossExpandEffect() {
  for (int size = 0; size < 4; size++) {
    clearCube();
    for (int layer = 0; layer < 8; layer++) {
      for (int row = 0; row < 8; row++) {
        if (row == 4 - size || row == 4 + size) cube[layer][row] = 0b11111111;
      }
    }
    updateCube();
    delay(150);
  }
}

uint8_t planePosition = 0;
uint8_t planeDirection = 0;
bool looped = false;

void planeBoing() {
  if (loading) {
    clearCube();
    uint8_t axis = random(0, 2);
    planePosition = random(0, 2) * 7;
    setPlane(axis, planePosition);
    if (axis == XAXIS) {
      if (planePosition == 0) {
        planeDirection = POS_X;
      } else {
        planeDirection = NEG_X;
      }
    } else if (axis == YAXIS) {
      if (planePosition == 0) {
        planeDirection = POS_Y;
      } else {
        planeDirection = NEG_Y;
      }
    } else if (axis == ZAXIS) {
      if (planePosition == 0) {
        planeDirection = POS_Z;
      } else {
        planeDirection = NEG_Z;
      }
    }
    timer = 0;
    looped = false;
    loading = false;
  }

  timer++;
  if (timer > PLANE_BOING_TIME) {
    timer = 0;
    shift(planeDirection);
    if (planeDirection % 2 == 0) {
      planePosition++;
      if (planePosition == 7) {
        if (looped) {
          loading = true;
        } else {
          planeDirection++;
          looped = true;
        }
      }
    } else {
      planePosition--;
      if (planePosition == 0) {
        if (looped) {
          loading = true;
        } else {
          planeDirection--;
          looped = true;
        }
      }
    }
  }
}

void pulseEffect() {
  static uint8_t pulseSize = 0;
  static bool expanding = true;

  if (loading) {
    clearCube();
    pulseSize = 1;
    expanding = true;
    loading = false;
  }

  timer++;
  if (timer > PULSE_TIME) {
    timer = 0;
    clearCube();
    
    if (expanding) {
      pulseSize++;
      if (pulseSize == 8) expanding = false;
    } else {
      pulseSize--;
      if (pulseSize == 1) expanding = true;
    }
    
    drawCube(4 - pulseSize / 2, 4 - pulseSize / 2, 4 - pulseSize / 2, pulseSize);
  }
}

void explosionEffect() {
  if (loading) {
    clearCube();
    loading = false;
  }

  timer++;
  if (timer > EXPLOSION_TIME) {
    timer = 0;
    clearCube();

    uint8_t cx = 4, cy = 4, cz = 4;
    for (uint8_t i = 0; i < 10; i++) {
      int dx = random(-3, 4);
      int dy = random(-3, 4);
      int dz = random(-3, 4);
      if (cx + dx < 8 && cy + dy < 8 && cz + dz < 8) {
        setVoxel(cx + dx, cy + dy, cz + dz);
      }
    }
  }
}

void bouncingBallEffect() {
  static uint8_t ballPosX = 0;
  static uint8_t ballPosY = 0;
  static uint8_t ballPosZ = 0;
  static int8_t xSpeed = 1;
  static int8_t ySpeed = 1;
  static int8_t zSpeed = 1;

  if (loading) {
    clearCube();
    ballPosX = random(0, 8);
    ballPosY = random(0, 8);
    ballPosZ = random(0, 8);
    xSpeed = random(1, 2);
    ySpeed = random(1, 2);
    zSpeed = random(1, 2);
    loading = false;
  }

  timer++;
  if (timer > BOUNCE_TIME) {
    timer = 0;
    clearCube();

    // วาดลูกบอล
    setVoxel(ballPosX, ballPosY, ballPosZ);

    // อัพเดทตำแหน่งลูกบอล
    ballPosX += xSpeed;
    ballPosY += ySpeed;
    ballPosZ += zSpeed;

    // เช็คการชนขอบ
    if (ballPosX == 0 || ballPosX == 7) xSpeed = -xSpeed;
    if (ballPosY == 0 || ballPosY == 7) ySpeed = -ySpeed;
    if (ballPosZ == 0 || ballPosZ == 7) zSpeed = -zSpeed;
  }
}

void heartbeatEffect() {
  static uint8_t heartbeatState = 0;

  if (loading) {
    clearCube();
    heartbeatState = 0;
    loading = false;
  }

  timer++;
  if (timer > HEARTBEAT_TIME) {
    timer = 0;

    if (heartbeatState == 0) {
      // ทำให้ไฟลุกขึ้นเล็กน้อย
      for (uint8_t i = 0; i < 8; i++) {
        for (uint8_t j = 0; j < 8; j++) {
          cube[i][j] = 0xFF;
        }
      }
      heartbeatState = 1;
    } else {
      // ทำให้ไฟหรี่ลง
      clearCube();
      heartbeatState = 0;
    }
    updateCube();
  }
}

void clearALL() {
  for (uint8_t x = 0; x < 8; x++) {
    for (uint8_t y = 0; y < 8; y++) {
      for (uint8_t z = 0; z < 8; z++) {
        setVoxel(x, y, z);  // ปิดไฟที่ (x, y, z)
      }
    }
  }
  updateCube();  // อัพเดตสถานะใหม่ให้ Cube
}

/////////////////////////////////////

////////// MATRIX KEYBOARD FUNCTION //////////

/////////////////////////////////////

////////// LCD DISPLAY FUNCTION //////////
char Setup_massage[20] = "  Setting   up  ";
char Raining_Effect[20] = "    Raining     ";
char Raining_Discription[20] = " Find a shelter ";
/////////////////////////////////////

////////// LCD DISPLAY FUNCTION //////////
void Settingup_Display() {
  lcd.setCursor(0, 0);
  for (int Loop = 0; Loop <= 16; Loop++) {
    lcd.print(Setup_massage[Loop]);
  }
}

void Raining_Status_Display() {
  lcd.setCursor(0, 0);
  for (int Loop = 0; Loop <= 16; Loop++) {
    lcd.print(Raining_Effect[Loop]);
  }
  lcd.setCursor(0, 1);
  for (int Loop = 0; Loop <= 16; Loop++) {
    lcd.print(Raining_Discription[Loop]);
  }
}
/////////////////////////////////////