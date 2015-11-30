#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <stdint.h>

#define CE_PIN 9
#define CSN_PIN 10
const uint64_t pipe1 = 0xE8E8F0F0A1LL;
const uint64_t pipe2 = 0xE8E8F0F0A2LL;
static int out = 1111;
static uint32_t answer;

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
  radio.setAutoAck(true);//allow RX send answer(acknoledgement) to TX (for ALL pipes?)
  radio.enableAckPayload(); //only for 0,1 pipes

  radio.stopListening();// ?
  radio.openWritingPipe(pipe2);
}

void loop()
{
  radio.stopListening();//?
  radio.write( &out, sizeof(out) );
  if ( radio.isAckPayloadAvailable() ) {
    radio.read(&answer, sizeof(answer)); //приемник принял и ответил
    Serial.print("Im TX. Received answer from RX: ");
    Serial.print(answer);
    Serial.print("\r\n");
  }
  delay(1000);
}
