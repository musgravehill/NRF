#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <stdint.h>
#include <OneWire.h> //for DS18B20

#define CE_PIN 7
#define CSN_PIN 8

const uint8_t imSensorNum = 3; //1..5

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

OneWire  ds(2);  // on pin 2 (a 4.7K resistor is necessary)
byte DS18B20_addr[8];


uint16_t getTemperatureNormalized() {
  byte i;
  byte present = 0;
  byte data[12];
  byte addr[8];
  float celsius, fahrenheit;

  if ( !ds.search(addr)) {
    //ds.reset_search();
    //delay(250);    
    return 0;
  }

  if (OneWire::crc8(addr, 7) != addr[7]) {
    return 0;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);        // start conversion, with parasite power on at the end

  //delay(1000);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.
  delay(1000);

  present = ds.reset();
  ds.select(addr);
  ds.write(0xBE);         // Read Scratchpad

  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
  }

  // Convert the data to actual temperature
  // because the result is a 16 bit signed integer, it should
  // be stored to an "int16_t" type, which is always 16 bits
  // even when compiled on a 32 bit processor.
  int16_t raw = (data[1] << 8) | data[0];
  byte cfg = (data[4] & 0x60);
  // at lower res, the low bits are undefined, so let's zero them
  if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
  else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
  else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
  //// default is 12 bit resolution, 750 ms conversion time
  
  celsius = (float)raw / 16.0;
  Serial.println(celsius, DEC); 

  return (uint16_t)raw;
}

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
  uint16_t messageToBase_temperature = getTemperatureNormalized(); // random(0, 65535); //2^16 - 1
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
  delay(8000);
}






