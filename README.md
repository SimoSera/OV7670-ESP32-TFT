# Changes from Original Repository
CLick [here](https://github.com/alankrantas/OV7670-ESP32-TFT) to see the original repository.

This is a branch in which I made this porject work with a ST7789 TFT display (instead of the ILI9341) and then I implemented multithreading for better performance and last i changed two pins (13->4 and 14->19) so that now the pins 12 to 15 are free to be used for another spi comunication (maybe a SD card reader)

For a more in dept description on the changes read [here](https://github.com/SimoSera/OV7670-ESP32-TFT/tree/main/OV7670_ESP32_TFT)

# Non-FIFO OV7670 Video on TFT with ESP32
Draw live color video of a non-FIFO OV7670 camera module on a 240x320 ST7789 TFT display using a generic ESP32 board. The script is based on the example from the [OV7670-ESP32](https://github.com/kobatan/OV7670-ESP32) driver.

> The official [esp32-camera](https://github.com/espressif/esp32-camera) only supports the FIFO version of OV7670s.

## Hardware

* ESP32 (Node32S or ESP32 DevKit V1 will do) - I used a bord siamilar to ESP32 DevKit V1
* non-FIFO OV7670 camera module
* 240x320 ST7789 TFT LCD display

All the hardware i used is from Aliexpress so it's probably not original.

## Drivers

* [OV7670-ESP32](https://github.com/kobatan/OV7670-ESP32) driver by kobatan. Download the .zip, extract it and move the ```OV7670-ESP32``` sub-directory (*not* the root) to the [Arduino library directory](https://docs.arduino.cc/hacking/software/Libraries).
* [Adafruit_GFX](https://github.com/adafruit/Adafruit-GFX-Library) and [Adafruit_T7789](https://github.com/adafruit/Adafruit-ST7735-Library)

If you have trouble flashing the ESP32, try press and hold the **boot** button and press **EN** once before flashing, and release **boot** when "Connecting....." shows up.

## Wiring

| OV7670 non-FIFO | ESP32 GPIO Pin |
| --- | --- |
| RESET | 3.3V |
| PWDN | GND |
| SSCB_SDA (SIOD) | 21 (pulled up with 1kΩ resistor) |
| SSCB_SCL (SIOC) | 22 (pulled up with 1kΩ resistor) |
| HREF | (not connected) |
| D0 | 36 |
| D1 | 39 |
| D2 | 34 |
| D3 | 35 |
| D4 | 32 |
| D5 | 33 |
| D6 | 25 |
| D7 | 26 |
| XCLK | 27 |
| PCLK | 19 |
| VSYNC | 4 |

| ST7789 TFT | ESP32 GPIO Pin |
| --- | --- |
| VCC | 3.3V |
| GND | GND |
| DC | 16 |
| CS | 5 |
| RES | 17 |
| SDA | 23 |
| SCL | 18 |
| BLK | (not connected) |

## Rotation and Resolution

Change the ```ROTATION``` and ```MODE``` definition in the script.

Due to the size of the screen, only the following resolutions are supported:

* ```QVGA``` (320X240)
* ```QQVGA``` (160x120)
* ```QCIF``` (176x144, cropped)
* ```QQCIF``` (88x72, cropped)
