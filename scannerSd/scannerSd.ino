/*  
  =SD=
    MOSI    11
    MISO    12
    CLK     13
    CS      4   
*/

#include <SdFat.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

const byte SD_CS =  4; //SS
SdFat SD_card;
File SD_file_log;
bool SD_isEnable = false;

const byte NRF_CSN =  10;
const byte NRF_CE =  8;
RF24 radio(NRF_CE, NRF_CSN); // Для Уно
const uint8_t NRF_channelsCount = 128; //channels for testing from 1 to 127
uint8_t NRF_collisionsOnChannelCount[NRF_channelsCount];
const int NRF_testChannelRetries = 100; //listen selected channel *** times to get RF-collisions or not

void setup(void) {
  pinMode(SD_CS, OUTPUT);    
  pinMode(10, OUTPUT); //hardware ATmega SPI SS
  pinMode(NRF_CSN, OUTPUT);
  
  delay(1000);
  Serial.begin(115200);
  SD_init();
  delay(1000);
  NRF_init();
}


void loop(void) {
  NRF_scanChannels();
  SD_writeScanResults();
}

void SD_writeScanResults() {
  int i = 0;  
  delay(10);
  if (SD_isEnable) {
    SD_file_log = SD_card.open("nrf.txt", FILE_WRITE);
    if (SD_file_log) {
      SD_file_log.print("\r\n");
      Serial.println("OK open file");
      // Print out header, high then low digit
      i = 0;
      while ( i < NRF_channelsCount )  {
        SD_file_log.print((i >> 4), HEX);
        ++i;
      }
      SD_file_log.print("\r\n");
      i = 0;
      while ( i < NRF_channelsCount )  {
        SD_file_log.print((i & 0xf), HEX);
        ++i;
      }
      SD_file_log.print("\r\n");

      //print results of scan
      i = 0;
      while ( i < NRF_channelsCount )  {
        SD_file_log.print(min(0xf, NRF_collisionsOnChannelCount[i] & 0xf), HEX);
        Serial.print(min(0xf, NRF_collisionsOnChannelCount[i] & 0xf), HEX);
        ++i;
      }
      SD_file_log.print("\r\n");
      SD_file_log.close();
      Serial.print("\r\n");
    }
    else {
      Serial.println("ERROR open file");
    }
  }  
}

void NRF_scanChannels() {
  // Clear measurement NRF_collisionsOnChannelCount
  memset(NRF_collisionsOnChannelCount, 0, sizeof(NRF_collisionsOnChannelCount));

  // Scan all channels NRF_testChannelRetries times
  int rep_counter = NRF_testChannelRetries;
  while (rep_counter--)  {
    int i = NRF_channelsCount;
    while (i--)    {
      // Select this channel
      radio.setChannel(i);

      // Listen for a little
      radio.startListening();
      delayMicroseconds(128);

      /*
        ___radio.testRPD()
        Test whether a signal (carrier or otherwise)
        greater than or equal to -64dBm is present on the channel
        only for +
        testRPD results are differ from testCarrier. Why?

        ___radio.testCarrier()
        for all nrf`s
      */

      // Did we get a carrier?
      if ( radio.testCarrier() ) {
        ++NRF_collisionsOnChannelCount[i];
      }
      radio.stopListening();
    }
  }
}

void SD_init() {  
  if (SD_card.begin(SD_CS, SPI_HALF_SPEED)) {
    SD_isEnable = true;
    Serial.println("SD init OK");
  } else {
    SD_isEnable = false;
    Serial.println("SD init ERROR");
  }  
}

void NRF_init() {
  radio.begin();
  delay(50);
  radio.setChannel(5);
  radio.setRetries(0, 0);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);
  radio.setCRCLength(RF24_CRC_16);
  radio.startListening();
  radio.printDetails();  // Вот эта строка напечатает нам что-то, если все правильно соединили.
  radio.stopListening();
}
