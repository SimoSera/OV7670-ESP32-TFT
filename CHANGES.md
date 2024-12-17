# Changes:
This version uses a ST7789 TFT diaply instead of the ILI9341 of the original repository so i changed the code to make it work.

Camera pins PCLK and VSYNC that were connected respctively to pins 14 and 13 are now connected to pins 19 and 4.
This was made to free pins 13 and 14 which could be used for another SPI connection becuase now pins 12(MISO) 13(MOSI) 14(SCLK) 15(CS0) are free altough pin 4(QHD) is being used.

With multithreading now one core is rendering the odd lines and the other core is rendering even lines, this way we can get more FPS and a smoother experience though there is still some tearing at QVGA resolution.

# Under Building:

When i will recieve the SD card reader module i will try to make it work with the rest.
