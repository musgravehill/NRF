#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <stdint.h>

void setup() {
  DS18B20_init();

  delay(2000);
  Serial.begin(9600);
  delay(100);

  NRF_init();
}

void loop() {
  uint16_t arrayToBase_batteryVoltage = random(0, 65535); //2^16 - 1
  uint16_t arrayToBase_temperature = 88; // getTemperatureNormalized(); // random(0, 65535); //2^16 - 1
  uint16_t arrayToBase_humidity = random(0, 65535); //2^16 - 1

  uint16_t arrayToBase[3] = {
    arrayToBase_batteryVoltage,
    arrayToBase_temperature,
    arrayToBase_humidity
  };

  NRF_sendData(arrayToBase);
  delay(4000);
}








