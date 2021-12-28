#ifndef MAIN_H_
#define MAIN_H_

#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>
#include <Seeed_BMP280.h>
#include "MQ9B.h"
#include "HCHO.h"
#include "PPD42.h"

#define MQ9B_PIN 33
#define HCHO_PIN 32
#define PPD42_PIN 34

BMP280 bmp280;
U8G2_SSD1306_128X64_ALT0_F_HW_I2C u8g2(U8G2_R2, U8X8_PIN_NONE); // SSD1306 and SSD1308Z are compatible
MQ9B mq9B(MQ9B_PIN);
HCHO hcho(HCHO_PIN);
PPD42 ppd42(PPD42_PIN);

#define LCDWidth        u8g2.getDisplayWidth()
#define ALIGN_CENTER(t) ((LCDWidth - (u8g2.getUTF8Width(t))) / 2)
#define PAGE_DELAY 10000

void draw();
void drawForecast();
void drawTemperature();
void drawPressure();
void drawHCHO();
void drawGas();
void drawDust();

typedef void (*Page_t)();
Page_t pages [] = {
    drawForecast,
    drawTemperature,
    drawPressure,
    drawHCHO,
    drawGas,
    drawDust
};

uint32_t startTime;
uint32_t sampleTime = 30000; // In ms

#endif //MAIN_H_
