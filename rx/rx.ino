#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <stdint.h>

#define CE_PIN 9
#define CSN_PIN 10

const uint64_t pipe0 = 0xDEADBEEF00LL; // pipe0 is SYSTEM_pipe, no reading
const uint64_t pipe1 = 0xDEADBEEF01LL;
const uint64_t pipe2 = 0xDEADBEEF02LL;
const uint64_t pipe3 = 0xDEADBEEF03LL;
const uint64_t pipe4 = 0xDEADBEEF04LL;
const uint64_t pipe5 = 0xDEADBEEF05LL;

static uint32_t messageIncoming;

//static uint8_t ackResponce0 = 200;
//static uint8_t ackResponce1 = 201;
//static uint8_t ackResponce2 = 202;
//static uint8_t ackResponce3 = 203;
//static uint8_t ackResponce4 = 204;
//static uint8_t ackResponce5 = 205;

static uint8_t availablePipeNum;

RF24 radio(CE_PIN, CSN_PIN);

void setup() {
  delay(2000);
  Serial.begin(9600);
  radio.begin();
  delay(100);
  radio.powerUp();
  delay(100);
  radio.setChannel(5);
  radio.setRetries(15, 15);
  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_MIN);
  radio.setCRCLength(RF24_CRC_8);

  radio.enableDynamicPayloads();//for ALL pipes, dynamic size of payload
  //radio.setPayloadSize(32); //uint_32t 32 bytes

  radio.setAutoAck(true);//allow RX send answer(acknoledgement) to TX (for ALL pipes?)
  radio.enableAckPayload(); //only for 0,1 pipes
  radio.enableDynamicAck(); //for ALL pipes?

  //radio.openReadingPipe(0, pipe0); pipe0 is SYSTEM_pipe, no reading
  radio.openReadingPipe(1, pipe1);
  //radio.openReadingPipe(2, pipe2);
  //radio.openReadingPipe(3, pipe3);
  //radio.openReadingPipe(4, pipe4);
  //radio.openReadingPipe(5, pipe5);
  radio.startListening();

  //attachInterrupt(0, check_radio, LOW); //send acknoledgement FAIL(
}

void check_radio() {
  //radio.writeAckPayload(0, &ackResponce0, sizeof(ackResponce0) ); pipe0 is SYSTEM_pipe, no reading
  //radio.writeAckPayload(1, &ackResponce1, sizeof(ackResponce1) );
  //radio.writeAckPayload(2, &ackResponce2, sizeof(ackResponce2) );
  //radio.writeAckPayload(3, &ackResponce3, sizeof(ackResponce3) );
  //radio.writeAckPayload(4, &ackResponce4, sizeof(ackResponce4) );
  //radio.writeAckPayload(5, &ackResponce5, sizeof(ackResponce5) ); 
  const byte resp = 22;
  radio.writeAckPayload(1, &resp, sizeof(resp) );
  if (radio.available(&availablePipeNum)) {
    radio.read( &messageIncoming, sizeof(messageIncoming) );  // по адресу записывает принятые данные;

    //responce = pipeNum, from Im receive data
    //radio.writeAckPayload((int)availablePipeNum, &availablePipeNum, sizeof(availablePipeNum) );


    //radio.stopListening();
    //radio.startListening();
    Serial.print("Im Base with IRQ and AckPayload. FromPipe sensor: ");
    Serial.print(availablePipeNum);
    Serial.print(" Message: ");
    Serial.print(messageIncoming);
    Serial.print("\r\n");
  }

  //bool tx, fail, rx;
  //radio.whatHappened(tx, fail, rx); // What happened?
  //if ( rx || radio.available()) {

}

void loop() {
  check_radio();
}
