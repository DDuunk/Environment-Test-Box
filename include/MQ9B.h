/**
 * @brief Detects mq9B leakage. Suitable for detecting LPG, CO & CH4.
 */
#ifndef MQ9B_H_
#define MQ9B_H_

#include <Arduino.h>

class MQ9B {

  uint8_t sensorPin;
  double calibrationValue;

 public:
  explicit MQ9B(uint8_t pin = 34);

  bool begin();
  double readGasAirRatio();
  double readGas();

 private:
  void calibrate();
  double readSensorVolt();

};

#endif //MQ9B_H_
