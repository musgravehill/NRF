#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <stdint.h>
#include "LowPower.h"

#define NRF_CE_PIN 7
#define NRF_CSN_PIN 8

uint16_t counterSleep_1s = 0;

void setup() {
  delay(2000);
  Serial.begin(9600);
  delay(100);

  NRF_init();
}

void loop() {
  LowPower.powerDown(SLEEP_1S, ADC_OFF, BOD_OFF);
  counterSleep_1s++;

  if (counterSleep_1s > 1) { //16 seconds
    counterSleep_1s = 0;
    sendDataToBase();
  }
}

void sendDataToBase() {
  uint16_t arrayToBase_batteryVoltage = random(0, 65535); //2^16 - 1
  uint16_t arrayToBase_temperature = 32; //2^16 - 1
  uint16_t arrayToBase_humidity = random(0, 65535); //2^16 - 1

  uint16_t arrayToBase[3] = {
    arrayToBase_batteryVoltage,
    arrayToBase_temperature,
    arrayToBase_humidity
  };

  NRF_sendData(arrayToBase);
}








