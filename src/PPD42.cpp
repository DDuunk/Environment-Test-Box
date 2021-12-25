#include "PPD42.h"

PPD42::PPD42(uint8_t pin, unsigned long sampleTime) {
  this->sensorPin = pin;
  this->sampleTime = sampleTime;
}

bool PPD42::begin() {
  pinMode(this->sensorPin, INPUT);
}

double PPD42::readConcentration() {
  double ratio = this->readRatio();
  double concentration = 1.1 * pow(ratio, 3) - 3.8 * pow(ratio, 2) + 520 * ratio + 0.62; // Using spec sheet curve

  Serial.print("|PPD42| Concentration: ");
  Serial.println(concentration);

  return concentration;
}

double PPD42::readRatio() {
  double ratio = this->readLowPulseOccupancy() / (this->sampleTime * 10.0);

  Serial.print("|PPD42| Ratio: ");
  Serial.println(ratio);

  return ratio;
}

unsigned long PPD42::readLowPulseOccupancy() {
  unsigned long lowPulseOccupancy = pulseIn(this->sensorPin, LOW);

  Serial.print("|PPD42| LPO: ");
  Serial.println(lowPulseOccupancy);

  return lowPulseOccupancy;
}


