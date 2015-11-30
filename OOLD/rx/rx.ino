#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <stdint.h>

#define CE_PIN 9
#define CSN_PIN 10

const uint64_t pipes[][6] = {
  0xDEADBEEF00LL,
  0xDEADBEEF01LL,
  0xDEADBEEF02LL,
  0xDEADBEEF03LL,
  0xDEADBEEF04LL,
  0xDEADBEEF05LL
};

static int in;
static uint8_t ackResponce = B11111111;

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
  //setPayloadSize (uint8_t size);
  radio.setAutoAck(true);//allow RX send answer(acknoledgement) to TX (for ALL pipes?)
  radio.enableAckPayload(); //only for 0,1 pipes

  radio.openReadingPipe(1, myPipe);
  radio.startListening();

  //attachInterrupt(0, check_radio, LOW); //send acknoledgement FAIL(
}

void check_radio() {
  radio.writeAckPayload(1, &message, sizeof(message) ); // Грузим сообщение для автоотправки;

  //bool tx, fail, rx;
  //radio.whatHappened(tx, fail, rx); // What happened?
  //if ( rx || radio.available()) {
  if (radio.available()) {
    radio.read( &in, sizeof(in) );  // по адресу переменной in функция записывает принятые данные;
    Serial.print("Im RX with IRQ and AckPayload. Received: ");
    Serial.print(in);
    Serial.print("\r\n");
  }

}

void loop() {
  check_radio();
}
