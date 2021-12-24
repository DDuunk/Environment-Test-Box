#include "HCHO.h"

HCHO::HCHO(uint8_t pin) {
  this->sensorPin = pin;
}

bool HCHO::begin() {
  calibrate();
}

void HCHO::calibrate() {
  uint16_t sensorValue = analogRead(this->sensorPin);
  this->calibrationValue = (1023.0 / sensorValue) - 1;
  Serial.print("HCHO - R0 = ");
  Serial.println(calibrationValue);
}

double HCHO::readHCHO() {
  uint16_t sensorValue = analogRead(this->sensorPin);
  double Rs = (1023.0 / sensorValue) - 1;

  Serial.print("HCHO - Rs = ");
  Serial.println(Rs);

  double ppm = pow(10.0, ((log10(Rs / this->calibrationValue) - 0.0827) / (-0.4807)));

  Serial.print("HCHO - HCHO ppm = ");
  Serial.println(ppm);

  return ppm;
}