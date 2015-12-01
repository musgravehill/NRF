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
  
  /* 
  ===writeAckPayload===enableDynamicPayloads=== 
  !  Only three of these can be pending at any time as there are only 3 FIFO buffers.
  !  Dynamic payloads must be enabled.
  !  write an ack payload as soon as startListening() is called
  */

  radio.enableDynamicPayloads();//for ALL pipes, dynamic size of payload
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

  //attachInterrupt(0, check_radio, LOW); //send acknoledgement FAIL
}

void radioListen() {   
  uint8_t currPipeNum;
  if (radio.available(&currPipeNum)) {
    radio.writeAckPayload(currPipeNum, &currPipeNum, sizeof(currPipeNum) );
    radio.read( &messageIncoming, sizeof(messageIncoming) ); 
    
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
  radioListen();
}
