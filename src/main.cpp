#include "main.h"

void setup() {
  Serial.begin(9600);
  u8g2.begin();

  if (!bmp280.init()) {
    Serial.println("BMP280 - Device Error!");
  }

  hcho.begin();
  mq9B.begin();
  ppd42.begin();

  startTime = millis();
}

void loop() {
  u8g2.clearBuffer(); // Clear internal memory

  for (auto & page : pages) {
    u8g2.firstPage();
    do {
      draw();
      page();
    } while (u8g2.nextPage());
    delay(PAGE_DELAY);
  }
}

void draw() {
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawFrame(0, 0, 128, 64);
}

void drawForecast() {
  uint32_t pressure = bmp280.getPressure() / 100;

  u8g2.drawStr(ALIGN_CENTER("Weather Forecast:"), 16, "Weather Forecast:");

  if (pressure <= 1000.59 && pressure > 998.5) {
    u8g2.drawStr(ALIGN_CENTER("Cloudy"), 56, "Cloudy");
  } else if (pressure < 998.5 && pressure > 996.5) {
    u8g2.drawStr(ALIGN_CENTER("Rain"), 56, "Rain");
  } else if (pressure > 1000.6 && pressure < 1050) {
    u8g2.drawStr(ALIGN_CENTER("Clear Sky"), 56, "Clear Sky");
  } else if (pressure > 990 && pressure <= 996.4) {
    u8g2.drawStr(ALIGN_CENTER("Storm"), 56, "Storm");
  } else {
    u8g2.drawStr(ALIGN_CENTER("Error!"),56, "Error!");
  }
}

void drawTemperature() {
  u8g2.drawStr(ALIGN_CENTER("Temperature:"), 16, "Temperature:");
  u8g2.setCursor(ALIGN_CENTER("xx.x x"), 56);
  u8g2.print(bmp280.getTemperature());
  u8g2.drawStr(80, 56, "C");
}

void drawPressure() {
  uint32_t pressure = bmp280.getPressure() / 100;
  u8g2.drawStr(ALIGN_CENTER("Pressure:"), 16, "Pressure:");
  u8g2.setCursor(ALIGN_CENTER("xxxx xxx"), 56);
  u8g2.print(pressure);
  u8g2.drawStr(66, 56, "hPa");
}

void drawHCHO() {
  u8g2.drawStr(ALIGN_CENTER("HCHO:"), 16, "HCHO:");
  u8g2.setCursor(ALIGN_CENTER("x.xx xxx"), 56);
  u8g2.print(hcho.readHCHO());
  u8g2.drawStr(66, 56, "ppm");
}

void drawGas() {
  u8g2.drawStr(ALIGN_CENTER("Gas:"), 16, "Gas:");
  u8g2.setCursor(ALIGN_CENTER("x.xx xxx"), 56);
  u8g2.print(mq9B.readGas());
  u8g2.drawStr(72, 56, "ppm");
}

void drawDust() {
  u8g2.drawStr(ALIGN_CENTER("Dust:"), 16, "Dust:");
  u8g2.setCursor(ALIGN_CENTER("xxx.xx xx/x^x"), 56);
  u8g2.print(ppd42.readConcentration());
  u8g2.drawStr(72, 56, "ug/m^3");
}