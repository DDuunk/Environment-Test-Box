#include "MQ9B.h"

MQ9B::MQ9B(uint8_t pin) {
  this->sensorPin = pin;
}

bool MQ9B::begin() {
  calibrate();
}

void MQ9B::calibrate() {
  double sensorVolt;
  double RSAir; //  Get the value of RS via in a clear air
  double sensorValue;

  // Get an average by testing 100 times
  for(int x = 0 ; x < 100 ; x++) {
    sensorValue = sensorValue + analogRead(this->sensorPin);
    delay(10);
  }
  sensorValue = sensorValue / 100.0;

  sensorVolt = sensorValue / 1024 * 5.0;
  RSAir = (5.0 - sensorVolt) / sensorVolt;
  this->calibrationValue = RSAir / 9.9; // The ratio of RS/R0 is 9.9 in LPG mq9B

  Serial.print("|MQ9B| [Calibration] SensorVolt: ");
  Serial.print(sensorVolt);
  Serial.print("V, CalibrationValue = ");
  Serial.println(this->calibrationValue);
}

double MQ9B::readGasAirRatio() {
  double RSGas = this->readGas();
  double ratio = RSGas / this->calibrationValue;

  Serial.print("|MQ9B| Rs/R0: ");
  Serial.println(ratio);

}

double MQ9B::readGas() {
  double sensorVolt = this->readSensorVolt();
  double RSGas = (5.0 - sensorVolt) / sensorVolt;

  Serial.print("|MQ9B| RSGas: ");
  Serial.println(RSGas);

  return RSGas;
}

double MQ9B::readSensorVolt() {
  double sensorVolt;
  uint8_t sensorValue = analogRead(this->sensorPin);
  delay(10);

  sensorVolt = (double) sensorValue / 1024 * 5.0;
  Serial.print("|MQ9B| SensorVolt: ");
  Serial.println(sensorVolt);

  return sensorVolt;
}