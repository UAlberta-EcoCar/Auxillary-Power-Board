#ifndef HISTORIGRAM_H_
#define HISTORIGRAM_H_

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "ADCRead.h"
#define OLED_RESET 4

void historigram_initialize(void);

void run_historigram(void);

#endif /* HISTORIGRAM_H_ */