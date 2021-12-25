/**
 * @brief Measures the Particulate Matter level (PM level) in the air
 * by counting the Low Pulse Ocupancy time (LPO time) in a given time unit.
 * LPO time is proportional to PM concentration.
 */
#ifndef PPD42_H_
#define PPD42_H_

#include <Arduino.h>
#include "ETB.h"

class PPD42 {

  uint8_t sensorPin;
  unsigned long sampleTime;

 public:
  explicit PPD42(uint8_t pin = 36, unsigned long sampleTime = 30000); // Sample 30S

  bool begin();
  double readConcentration();
  double readRatio();
  unsigned long readLowPulseOccupancy();

};

#endif //PPD42_H_
