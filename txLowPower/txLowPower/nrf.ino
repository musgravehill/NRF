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

RF24 NRF_radio(NRF_CE_PIN, NRF_CSN_PIN);

void NRF_init() {
  Serial.print(F("Im Sensor# "));
  Serial.print(imSensorNum);
  Serial.print(F("\r\n"));

  NRF_radio.begin();
  delay(100);
  NRF_radio.powerUp();
  delay(50);
  radio.setChannel(0x6D);
  radio.setRetries(15, 15);
  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_LOW);
  radio.setCRCLength(RF24_CRC_16);

  /*
    ===writeAckPayload===enableDynamicPayloads===
    !  Only three of these can be pending at any time as there are only 3 FIFO buffers.
    !  Dynamic payloads must be enabled.
    !  write an ack payload as soon as startListening() is called
  */
  NRF_radio.enableDynamicPayloads();//for ALL pipes
  //NRF_radio.setPayloadSize(32); //32 bytes? Can corrupt "writeAckPayload"?

  NRF_radio.setAutoAck(true);//allow RX send answer(acknoledgement) to TX (for ALL pipes?)
  NRF_radio.enableAckPayload(); //only for 0,1 pipes?
  //NRF_radio.enableDynamicAck(); //for ALL pipes? Чтобы можно было вкл\выкл получение ACK?

  NRF_radio.stopListening();// ?
  NRF_radio.openWritingPipe(pipes[imSensorNum]); //pipe0 is SYSTEM_pipe, no reading

  NRF_radio.powerDown();
}

void NRF_sendData(uint16_t *arrayToBase) {
  uint8_t answerFromBase; //2^8 - 1   [0,255]

  NRF_radio.powerUp();
  delay(50);

  //Stop listening for incoming messages, and switch to transmit mode.
  //Do this before calling write().
  NRF_radio.stopListening();
  NRF_radio.write( &arrayToBase, sizeof(arrayToBase));

  Serial.print(F("V= "));
  Serial.print(arrayToBase[0]);
  Serial.print(F("\r\n"));
  Serial.print(F("t= "));
  Serial.print(arrayToBase[1]);
  Serial.print(F("\r\n"));
  Serial.print(F("h= "));
  Serial.print(arrayToBase[2]);
  Serial.print(F("\r\n"));

  if ( NRF_radio.isAckPayloadAvailable() ) {
    NRF_radio.read(&answerFromBase, sizeof(answerFromBase)); //приемник принял и ответил

    Serial.print(F("__Received answer from Base: "));
    Serial.print(answerFromBase, DEC);
    Serial.print(F("\r\n"));
  }

  delay(50);
  NRF_radio.powerDown();
}
