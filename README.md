# Changes from Original Repository
CLick [here](https://github.com/alankrantas/OV7670-ESP32-TFT) to see the original repository.

I modified the code to make this project work with ST7789 TFT display (instead of the ILI9341) and I implemented multithreading for better performance. I also changed two pins connections (13->4 and 14->19) so that now the pins 12 to 15 are free to be used for another spi comunication (maybe a SD card reader)

For a more in dept description on the changes read [here](https://github.com/SimoSera/OV7670-ESP32-TFT/blob/main/CHANGES.md)

# Non-FIFO OV7670 Video on TFT with ESP32
Draw live color video from a non-FIFO OV7670 camera module on a 240x320 ST7789 TFT display using an ESP32 board. The script is based on the example from the [OV7670-ESP32](https://github.com/kobatan/OV7670-ESP32) driver.

> The official [esp32-camera](https://github.com/espressif/esp32-camera) only supports the FIFO version of OV7670s.

# Getting Started

## Hardware

* ESP32 (Node32S or ESP32 DevKit V1 will do) - I used a clone of ESP32 DevKit V1
* non-FIFO OV7670 camera module
* 240x320 ST7789 TFT LCD display


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

## Libraries

To work this project needs a couple of libraries. This code (at the time of writing this) works with the latest versions of Arduino IDE and ESP32 firmware.

The libraries needed are:
* Custom OV7670 and I2SCamera libraries originally from [this library](https://github.com/kobatan/OV7670-ESP32) but modified to work with the latest libraries and firmware. So to make the code work you need to download the ```OV7670.h```, ```OV7670.cpp```, ```I2SCamera.h``` and ```I2SCamera.cpp``` files.
* [Adafruit_GFX](https://github.com/adafruit/Adafruit-GFX-Library)
* [Adafruit_ST7789](https://github.com/adafruit/Adafruit-ST7735-Library) (this library is made for both ST7735 and ST7789)

If you have trouble flashing the ESP32, try press and hold the **boot** button and press **EN** once before flashing, and release **boot** when "Connecting....." shows up.


## Rotation and Resolution

Change the ```ROTATION``` and ```MODE``` definition in the script.

When choosing the ```MODE``` remember that increasing the quality decreases speed and vice versa. It still works at good speed even in the 320x240 mode.

Due to the size of the screen, only the following resolutions are supported:

* ```QVGA``` (320X240)
* ```QQVGA``` (160x120)
* ```QCIF``` (176x144, cropped)
* ```QQCIF``` (88x72, cropped)
