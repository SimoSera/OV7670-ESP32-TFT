// Non-FIFO OV7670 Video on TFT with ESP32
// based on https://github.com/kobatan/OV7670-ESP32
/*
 * 
 * (not tested)
 * could fit an sd card reader on spi pins:
 * 12 13 14 15
 * remember that pin 12 is dangeroud: boot fails if pulled high, strapping pin
 * other pins that are free: 0 1 2 3 (0 1 3 are special pins that should not be used and 2 is onboard led)
 */

#define MODE QVGA  // 320 X 240
//#define MODE      QQVGA  // 160 x 120
//#define MODE      QCIF  // 176 x 144 (crop)
//#define MODE      QQCIF  //  88 x 72 (crop)

#define COLOR RGB565
//#define COLOR     YUV422

#define ROTATION 1  // 0~4

#include <Wire.h>
#include <SPI.h>
#include <OV7670.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

// OV7670 pins
// SSCB_SDA(SIOD) -> 21(ESP32)
// SSCB_SCL(SIOC) -> 22(ESP32)
// RESET          -> 3.3V
// PWDN            -> GND
// HREF           -> NC
const camera_config_t cam_conf = {
  .D0 = 36,
  .D1 = 39,
  .D2 = 34,
  .D3 = 35,
  .D4 = 32,
  .D5 = 33,
  .D6 = 25,
  .D7 = 26,
  .XCLK = 27,
  .PCLK = 19,  //14
  .VSYNC = 4,  //13
  .xclk_freq_hz = 10000000,  // XCLK 10MHz
  .ledc_timer = LEDC_TIMER_0,
  .ledc_channel = LEDC_CHANNEL_0
};

// TFT pins
#define TFT_CS         5
#define TFT_RST        17 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC         16


Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
OV7670 cam;
uint16_t *buf1,*buf2, w, h;
//MultiThreading
TaskHandle_t Task1;
void Task1code(void * pvParameters){
  for(;;){
    for (uint16_t y = 0; y < h; y+=2) {
      buf1 = cam.getLine(y + 1);
      tft.drawRGBBitmap(0, y, buf1, w, 1);
    }
  }
}



void setup() {
  setCpuFrequencyMhz(240);

  Serial.begin(9600);
  
  Wire.begin();
  Wire.setClock(400000);
  tft.init(240, 320);
  tft.setRotation(ROTATION);
  tft.fillScreen(ST77XX_BLACK);

  esp_err_t err = cam.init(&cam_conf, MODE, COLOR);
  if (err != ESP_OK) Serial.println("cam.init ERROR");

  cam.setPCLK(2, DBLV_CLK_x4);
  cam.vflip(false);
  Serial.printf("cam MID = %X\n\r", cam.getMID());
  Serial.printf("cam PID = %X\n\r", cam.getPID());

  switch (MODE) {
    case QVGA:
      w = 320;
      h = 240;
      break;
    case QQVGA:
      w = 160;
      h = 120;
      break;
    case QCIF:
      w = 176;
      h = 144;
      break;
    case QQCIF:
      w = 88;
      h = 72;
  }
  xTaskCreatePinnedToCore(
      Task1code, /* Function to implement the task */
      "Task1", /* Name of the task */
      10000,  /* Stack size in words */
      NULL,  /* Task input parameter */
      0,  /* Priority of the task */
      &Task1,  /* Task handle. */
      0); /* Core where the task should run */
}

void loop(void) {
  for (uint16_t y = 1; y < h; y+=2) {
      buf2 = cam.getLine(y + 1);
      tft.drawRGBBitmap(0, y, buf2, w, 1);
    }
}
