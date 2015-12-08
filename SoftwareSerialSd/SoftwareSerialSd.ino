/*
  Note:
  Not all pins on the Mega and Mega 2560 support change interrupts,
  so only the following can be used for RX:
  10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69


*/
#include <SoftwareSerial.h>
#include <SdFat.h>
#include <SPI.h>

const byte SD_CS =  4; //SS
SdFat SD_card;
File SD_file_log;
bool SD_isEnable = false;

SoftwareSerial mySerial(7, 8); // RX, TX

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  pinMode(SD_CS, OUTPUT);
  pinMode(10, OUTPUT); //hardware ATmega SPI SS

  SD_init();
}

void loop() { // run over and over
  if (mySerial.available()) {
    char getByte = mySerial.read();
    Serial.write(getByte);
    if (SD_isEnable) {
      SD_file_log = SD_card.open("events.txt", FILE_WRITE);
      if (SD_file_log) {
        Serial.println("OK open file");
        SD_file_log.print(getByte);
        SD_file_log.close();
      }
      else {
        Serial.println("ERROR open file");
      }
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

