#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <stdint.h>
#include "LowPower.h"

#define NRF_CE_PIN 7
#define NRF_CSN_PIN 8

uint16_t counterSleep_8s = 0;

void setup() {
  delay(2000);
  Serial.begin(9600);
  NRF_init();
}

void loop() {
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  counterSleep_8s++;

  if (counterSleep_8s > 0) {
    counterSleep_8s = 0;
    sendDataToBase();
  }  
}

void sendDataToBase() {
  uint16_t batteryVoltage = random(0, 65535); //2^16 - 1
  uint16_t temperature = 777; //2^16 - 1
  uint16_t humidity = random(0, 65535); //2^16 - 1

  NRF_sendData(batteryVoltage, temperature, humidity );
}








