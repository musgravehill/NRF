/** SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4
*/


#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
#include <SD.h>

const byte SD_CS =  4; //SS
const byte SD_LVC_OE = 2; //1 == enable LVC, 0 ==disable LVC
Sd2Card card;
File SD_file_nrf_log;

const byte NRF_CSN =  8;
const byte NRF_CE =  7;
RF24 radio(NRF_CE, NRF_CSN); // Для Уно
const uint8_t num_channels = 128;
uint8_t values[num_channels];
const int num_reps = 100;

void setup(void) {
  pinMode(SD_CS, OUTPUT);
  pinMode(SD_LVC_OE, OUTPUT);
  SD_disable();

  delay(2000);
  Serial.begin(9600);
  printf_begin();

  delay(50);
  SD_enable();
  if (!card.init(SPI_HALF_SPEED, SD_CS)) {
    Serial.println("initialization failed. Things to check:");
  } else {
    Serial.println("Wiring is correct and a card is present.");

  }
  SD_disable();

  delay(50);
  radio.begin();
  delay(50);
  radio.setChannel(5);
  radio.setRetries(15, 15);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_LOW);
  radio.setCRCLength(RF24_CRC_8);
  radio.startListening();
  radio.printDetails();  // Вот эта строка напечатает нам что-то, если все правильно соединили.
  if (radio.isPVariant()) {
    Serial.println("Im real NRF");
  } else {
    Serial.println("Im FAKE NRF");
  }
  radio.stopListening();

  // Print out header, high then low digit
  int i = 0;
  while ( i < num_channels )
  {
    printf("%x", i >> 4);
    ++i;
  }
  Serial.println();
  i = 0;
  while ( i < num_channels )
  {
    printf("%x", i & 0xf);
    ++i;
  }
  Serial.println();

}


void loop(void) {

  // Clear measurement values
  memset(values, 0, sizeof(values));

  // Scan all channels num_reps times
  int rep_counter = num_reps;
  while (rep_counter--)  {
    int i = num_channels;
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
        ++values[i];
      }
      radio.stopListening();
    }
  }

  // Print out channel measurements, clamped to a single hex digit
  int i = 0;
  SD_file_nrf_log = SD.open("nrf.txt", FILE_WRITE);
  while ( i < num_channels )
  {
    //Serial.print(".");
    //Serial.print(values[i], DEC);
    printf("%x", min(0xf, values[i] & 0xf));
    if (SD_file_nrf_log) {
      SD_file_nrf_log.println(min(0xf, values[i] & 0xf));
    }
    ++i;
  }
  SD_file_nrf_log.close();
  Serial.println();

}

void SD_enable() {
  digitalWrite(SD_CS, 0);
  digitalWrite(SD_LVC_OE, 1);
}
void SD_disable() {
  digitalWrite(SD_CS, 1);
  digitalWrite(SD_LVC_OE, 0);
}
