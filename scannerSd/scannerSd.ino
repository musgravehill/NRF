/** SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4
*/

#include <SD.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"


Sd2Card card;

const byte sdCS =  4; //SS
const byte nrfCSn =  8;
const byte nrfCE =  7;

RF24 radio(nrfCE, nrfCSn); // Для Уно
const uint8_t num_channels = 128;
uint8_t values[num_channels];



void setup(void) {
  pinMode(sdCS, OUTPUT);
  pinMode(nrfCSn, OUTPUT);

  //sdDisable();

  delay(3000);
  Serial.begin(9600);
  printf_begin();

  radio.begin();
  delay(50);
  radio.setChannel(5);
  radio.setRetries(15, 15);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_MAX);
  radio.setCRCLength(RF24_CRC_8);
  radio.startListening();
  radio.printDetails();  // Вот эта строка напечатает нам что-то, если все правильно соединили.
  if (radio.isPVariant()) {
    Serial.println("Im real NRF");
  } else {
    Serial.println("Im FAKE NRF");
  }
  radio.stopListening();




  if (!card.init(SPI_HALF_SPEED, sdCS)) {
    Serial.println("initialization failed. Things to check:");
  } else {
    Serial.println("Wiring is correct and a card is present.");
  }
}


void loop(void) {
}

void sdEnable() {
  digitalWrite(sdCS, 0);
}
void sdDisable() {
  digitalWrite(sdCS, 1);
}
void nrfEnable() {
  digitalWrite(nrfCSn, 0);
}
void nrfDisable() {
  digitalWrite(nrfCSn, 1);
}


