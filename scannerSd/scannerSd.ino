/** SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4
*/

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <SD.h>

File myFile;

RF24 radio(9, 10); // Для Уно
//RF24 radio(9,53);// Для Меги
const uint8_t num_channels = 128;
uint8_t values[num_channels];

const byte sdCS =  4; //SS
const byte nrfCS =  10;  //CSN, NOT CE

void setup(void) {
  pinMode(sdCS, OUTPUT);
  pinMode(nrfCS, OUTPUT);
  digitalWrite(sdCS, 1);
  digitalWrite(nrfCS, 1);

  delay(3000);
  Serial.begin(57600);
  printf_begin();
  radio.begin();
  delay(50);
  radio.setChannel(0);

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
  delay(5000);              // И посмотрим на это пять секунд.

  radio.stopListening();
  int i = 0;    // А это напечатает нам заголовки всех 127 каналов
  while ( i < num_channels )  {
    printf("%x", i >> 4);
    ++i;
  }
  printf("\n\r");
  i = 0;
  while ( i < num_channels ) {
    printf("%x", i & 0xf);
    ++i;
  }
  printf("\n\r");
}
const int num_reps = 100;

void loop(void)
{

  digitalWrite(sdCS, 1); //disable
  digitalWrite(nrfCS, 0); //enable

  memset(values, 0, sizeof(values));
  int rep_counter = num_reps;
  while (rep_counter--) {
    int i = num_channels;
    while (i--) {
      radio.setChannel(i);
      radio.startListening();
      delayMicroseconds(128);
      radio.stopListening();
      if ( radio.testCarrier() )
        ++values[i];
    }
  }

  radio.stopListening();
  digitalWrite(nrfCS, 1); //disable
  digitalWrite(sdCS, 0); //enable


  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization SD done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {

    int i = 0;
    while ( i < num_channels ) {
      printf("%x", min(0xf, values[i] & 0xf));
      myFile.print(min(0xf, values[i] & 0xf));
      myFile.print("\r\n");
      ++i;
    }

    // close the file:
    myFile.close();

  } else {
    Serial.println("error opening test.txt");
  }



  printf("\n\r");
}
int serial_putc( char c, FILE * ) {
  Serial.write( c );
  return c;
}

void printf_begin(void) {
  fdevopen( &serial_putc, 0 );
}
