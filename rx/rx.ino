#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <stdint.h>

#define CE_PIN 9
#define CSN_PIN 10

//'static' - no need
const uint64_t pipes[6] = {
  0xDEADBEEF00LL,  //pipe0 is SYSTEM_pipe, avoid openReadingPipe(0, );
  0xDEADBEEF01LL,
  0xDEADBEEF02LL,
  0xDEADBEEF03LL,
  0xDEADBEEF04LL,
  0xDEADBEEF05LL
};

uint8_t currPipeNum;
uint16_t messageFromSensor[3] = {
  0, //v
  0, //t
  0  //h
};

RF24 radio(CE_PIN, CSN_PIN);

void setup() {
  delay(2000);
  Serial.begin(9600);
  delay(100);
  Serial.println("Im Base with IRQ and AckPayload");

  radio.begin();
  delay(100);
  radio.powerUp();
  delay(100);
  radio.setChannel(5);
  radio.setRetries(15, 15);
  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_MIN);
  radio.setCRCLength(RF24_CRC_8);

  /*
    ===writeAckPayload===enableDynamicPayloads===
    !  Only three of these can be pending at any time as there are only 3 FIFO buffers.
    !  Dynamic payloads must be enabled.
    !  write an ack payload as soon as startListening() is called
  */
  radio.enableDynamicPayloads();//for ALL pipes
  //radio.setPayloadSize(32); //32 bytes? Can corrupt "writeAckPayload"?

  radio.setAutoAck(true);//allow RX send answer(acknoledgement) to TX (for ALL pipes?)
  radio.enableAckPayload(); //only for 0,1 pipes?
  //radio.enableDynamicAck(); //for ALL pipes? Чтобы можно было вкл\выкл получение ACK?

  //radio.openReadingPipe(0, pipe0); 0 is SYSTEM, no reading
  radio.openReadingPipe(1, pipes[1]);
  radio.openReadingPipe(2, pipes[2]);
  radio.openReadingPipe(3, pipes[3]);
  radio.openReadingPipe(4, pipes[4]);
  radio.openReadingPipe(5, pipes[5]);
  radio.startListening();

  attachInterrupt(0, radioListen, LOW); //d2  //send acknoledgement FAIL
}

void radioListen() {

  if (radio.available(&currPipeNum)) {
    radio.writeAckPayload(currPipeNum, &currPipeNum, sizeof(currPipeNum) );
    if (radio.getDynamicPayloadSize() > 1) { //размер полученного сообщения
      radio.read(&messageFromSensor, sizeof(messageFromSensor));

      Serial.print("Sensor# ");
      Serial.print(currPipeNum);
      Serial.print("\r\n");
      Serial.print("V= ");
      Serial.print(messageFromSensor[0]);
      Serial.print("\r\n");
      Serial.print("t= ");
      Serial.print(messageFromSensor[1]);
      Serial.print("\r\n");
      Serial.print("h= ");
      Serial.print(messageFromSensor[2]);
      Serial.print("\r\n");
      Serial.print("\r\n");
    }
    else {
      // Corrupt payload has been flushed
    }

    //radio.stopListening(); //не надо! СТОП только если хочешь write
    //radio.startListening();//не надо! СТАРТ один раз, когда объявил трубы

  }
  //bool tx, fail, rx;
  //radio.whatHappened(tx, fail, rx); // What happened?
  //if ( rx || radio.available()) {

}

void loop() {
  //radioListen();
}


