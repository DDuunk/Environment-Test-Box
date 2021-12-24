/**
 * @brief Detects VOCs (Volatile organic compounds) with a HCHO Sensor.
 * Sensor can detecct gasses whose concentration is up to 1ppm.
 * Suitable for detecting formaldehyde, benzene, toluene and other
 * volatile components.
 */
#ifndef HCHO_H_
#define HCHO_H_

#include <Arduino.h>

class HCHO {

  uint8_t sensorPin;
  double calibrationValue;

 public:
  explicit HCHO(uint8_t pin = A0);

  bool begin();
  double readHCHO();

 private:
  void calibrate();

};

#endif //HCHO_H_
