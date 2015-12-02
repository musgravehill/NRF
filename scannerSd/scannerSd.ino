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


Sd2Card card;
SdVolume volume;

RF24 radio(9, 10); // Для Уно
const uint8_t num_channels = 128;
uint8_t values[num_channels];

const byte sdCS =  4; //SS
const byte nrfCSn =  10;  //CSN, NOT CE

void setup(void) {
  pinMode(sdCS, OUTPUT);
  pinMode(nrfCSn, OUTPUT);

  sdDisable();
  nrfDisable();

  delay(3000);
  Serial.begin(9600);  

  if (!card.init(SPI_HALF_SPEED, sdCS)) {
    Serial.println("initialization failed. Things to check:");
  } else {
    Serial.println("Wiring is correct and a card is present.");
  }
  uint32_t volumesize;
  Serial.print("\nVolume type is FAT");
  Serial.println(volume.fatType(), DEC);
  Serial.println(" ");

  sdDisable();
  nrfDisable();  

  radio.begin();
  delay(50);
  radio.setChannel(0);

  radio.setRetries(15, 15);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_MAX);
  radio.setCRCLength(RF24_CRC_8);
}


void loop(void)
{
  radio.startListening();

  radio.printDetails();  // Вот эта строка напечатает нам что-то, если все правильно соединили.

  if (radio.isPVariant()) {
    Serial.println("Im real NRF");
  } else {
    Serial.println("Im FAKE NRF");
  }
  radio.stopListening();

  delay(3000);
}

void sdEnable() {
  digitalWrite(sdCS, 0);
}
void sdDisable() {
  digitalWrite(sdCS, 1);
}
void nrfEnable() {
  digitalWrite(nrfCSn, 1);
}
void nrfDisable() {
  digitalWrite(nrfCSn, 0);
}



int vserial_putc( char c, FILE * ) {
  //Serial.write( c );
  //return c;
}

void vprintf_begin(void) {
  //  fdevopen( &serial_putc, 0 );
}
