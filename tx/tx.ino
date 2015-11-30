#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <stdint.h>

#define CE_PIN 9
#define CSN_PIN 10

const uint64_t pipe0 = 0xDEADBEEF00LL;  //pipe0 is SYSTEM_pipe, no reading, no writing
const uint64_t pipe1 = 0xDEADBEEF01LL;
const uint64_t pipe2 = 0xDEADBEEF02LL;
const uint64_t pipe3 = 0xDEADBEEF03LL;
const uint64_t pipe4 = 0xDEADBEEF04LL;
const uint64_t pipe5 = 0xDEADBEEF05LL;

static int messageToBase = 11111;
static uint32_t answerFromBase;

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
  //radio.enableDynamicAck(); //for ALL pipes?

  radio.stopListening();// ?
  radio.openWritingPipe(pipe1); //pipe0 is SYSTEM_pipe, no reading
}

void loop()
{
  radio.stopListening();//?
  radio.write( &messageToBase, sizeof(messageToBase));

  Serial.print("Im Sensor. Send to Base: ");
  Serial.print(messageToBase);
  Serial.print("\r\n");

  if ( radio.isAckPayloadAvailable() ) {
    radio.read(&answerFromBase, sizeof(answerFromBase)); //приемник принял и ответил

    Serial.print("___Received answer from Base: ");
    Serial.print(answerFromBase);
    Serial.print("\r\n");
  }
  delay(1000);
}
