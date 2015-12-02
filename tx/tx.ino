#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <stdint.h>

#define CE_PIN 9
#define CSN_PIN 10

const uint8_t imSensorNum = 1; //1..5

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
  delay(100);
  Serial.print(F("Im Sensor# "));
  Serial.print(imSensorNum);
  Serial.print(F("\r\n"));  

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

  radio.stopListening();// ?
  radio.openWritingPipe(pipes[imSensorNum]); //pipe0 is SYSTEM_pipe, no reading
}

void loop()
{
  uint16_t messageToBase_batteryVoltage = random(0, 65535); //2^16 - 1 
  uint16_t messageToBase_temperature = random(0, 65535); //2^16 - 1 
  uint16_t messageToBase_humidity = random(0, 65535); //2^16 - 1 

  uint16_t messageToBase[3] = { 
    messageToBase_batteryVoltage,
    messageToBase_temperature,
    messageToBase_humidity
  };

  uint8_t answerFromBase; //2^8 - 1   [0,255]

  //Stop listening for incoming messages, and switch to transmit mode. 
  //Do this before calling write().
  radio.stopListening(); 
  radio.write( &messageToBase, sizeof(messageToBase));

  Serial.print(F("V= "));
  Serial.print(messageToBase[0]);
  Serial.print(F("\r\n"));
  Serial.print(F("t= "));
  Serial.print(messageToBase[1]);
  Serial.print(F("\r\n"));
  Serial.print(F("h= "));
  Serial.print(messageToBase[2]);
  Serial.print(F("\r\n")); 

  if ( radio.isAckPayloadAvailable() ) {
    radio.read(&answerFromBase, sizeof(answerFromBase)); //приемник принял и ответил

    Serial.print(F("__Received answer from Base: "));
    Serial.print(answerFromBase, DEC);  
    Serial.print(F("\r\n"));  
  }
  delay(1000);
}






