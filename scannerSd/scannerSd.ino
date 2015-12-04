/*
  SD hold MISO in HIGH state forever => other SPI devicies cannot work, cause they waiting for MISO LOW.
  So, you need to disconnect MISO, VCC or ALL pins of SD at the end of use.
  How it works: enable_LVC, work with SD, disable_LVC.
  SD --- LVC with OE pin --- Arduino
    MOSI    11
    MISO    12
    CLK     13
    CS      4
    LVC_OE  2  //1 == enable LVC, 0 ==disable LVC

    LVC_VA=3.3V
    LVC_VB=5V
*/


#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <SD.h>

const byte SD_CS =  4; //SS
const byte SD_LVC_OE = 2;
Sd2Card card;
File SD_fileNrfLog;
bool SD_isEnable = false;

const byte NRF_CSN =  8;
const byte NRF_CE =  7;
RF24 radio(NRF_CE, NRF_CSN); // Для Уно
const uint8_t NRF_channelsCount = 128; //channels for testing from 1 to 127
uint8_t NRF_collisionsOnChannelCount[NRF_channelsCount];
const int NRF_testChannelRetries = 100; //listen selected channel *** times to get RF-collisions or not

void setup(void) {
  delay(1000);
  Serial.begin(9600);
  SD_init();
  delay(1000);
  NRF_init();
}


void loop(void) {
  NRF_scanChannels(); 
}

void SD_writeScanResults() {
  SD_enable();
  delay(10);
  if (SD_isEnable) {
    SD_fileNrfLog = SD.open("nrf.txt", FILE_WRITE);
    if (SD_fileNrfLog) {
      // Print out header, high then low digit
      int i = 0;
      while ( i < NRF_channelsCount )  {
        SD_fileNrfLog.print((i >> 4), HEX);
        ++i;
      }
      Serial.println();
      i = 0;
      while ( i < NRF_channelsCount )  {
        SD_fileNrfLog.print((i & 0xf), HEX);
        ++i;
      }
      //print results of scan
      while ( i < NRF_channelsCount )  {
        SD_fileNrfLog.print(min(0xf, NRF_collisionsOnChannelCount[i] & 0xf), HEX);
        SD_fileNrfLog.print("\r\n");
        ++i;
      }
      SD_fileNrfLog.close();
    }
  }
  SD_disable();
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
  pinMode(SD_CS, OUTPUT);
  pinMode(SD_LVC_OE, OUTPUT);
  SD_disable();
  delay(50);
  SD_enable();
  if (card.init(SPI_HALF_SPEED, SD_CS)) {
    SD_isEnable = false;
    Serial.println("SD init OK");
  } else {
    SD_isEnable = false;
    Serial.println("SD init ERROR");
  }
  SD_disable();
}

void NRF_init() {
  radio.begin();
  delay(50);
  radio.setChannel(5);
  radio.setRetries(0, 0);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);
  radio.setCRCLength(RF24_CRC_8);
  radio.startListening();
  radio.printDetails();  // Вот эта строка напечатает нам что-то, если все правильно соединили.
  radio.stopListening();
}

void SD_enable() {
  digitalWrite(SD_CS, 0);
  digitalWrite(SD_LVC_OE, 1);
}
void SD_disable() {
  digitalWrite(SD_CS, 1);
  digitalWrite(SD_LVC_OE, 0);
}
