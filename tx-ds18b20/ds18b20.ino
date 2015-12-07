//for DS18B20 -55°C to +125°C
#define DS18B20_PIN 2
//void OneWireReset(int Pin);
//void OneWireOutByte(int Pin, byte d);
//byte OneWireInByte(int Pin);
//void DS18B20_init();


void DS18B20_init() {
  digitalWrite(DS18B20_PIN, LOW);
  pinMode(DS18B20_PIN, INPUT);
}

uint16_t getTemperatureNormalized() {
  int HighByte, LowByte, TReading, SignBit, Tc_100, Whole, Fract;

  OneWireReset(DS18B20_PIN);
  OneWireOutByte(DS18B20_PIN, 0xcc);
  OneWireOutByte(DS18B20_PIN, 0x44); // perform temperature conversion, strong pullup for one sec

  OneWireReset(DS18B20_PIN);
  OneWireOutByte(DS18B20_PIN, 0xcc);
  OneWireOutByte(DS18B20_PIN, 0xbe);

  LowByte = OneWireInByte(DS18B20_PIN);
  HighByte = OneWireInByte(DS18B20_PIN);
  TReading = (HighByte << 8) + LowByte;
  SignBit = TReading & 0x8000;  // test most sig bit
  if (SignBit) // negative
  {
    TReading = (TReading ^ 0xffff) + 1; // 2's comp
  }
  Tc_100 = (6 * TReading) + TReading / 4;    // multiply by (100 * 0.0625) or 6.25
  Whole = Tc_100 / 100;  // separate off the whole and fractional portions
  if (SignBit) { // If its negative
    Whole *= -1;
  }
  Serial.println(Whole);
  /*
    Fract = Tc_100 % 100;
    Serial.print(".");
    if (Fract < 10)
    {
    Serial.print("0");
    }
    Serial.println(Fract);
  */
  return Whole + 100; // -55C => 45; 28C => 128
}

void OneWireReset(int Pin) // reset.  Should improve to act as a presence pulse
{
  digitalWrite(Pin, LOW);
  pinMode(Pin, OUTPUT); // bring low for 500 us
  delayMicroseconds(500);
  pinMode(Pin, INPUT);
  delayMicroseconds(500);
}

void OneWireOutByte(int Pin, byte d) // output byte d (least sig bit first).
{
  byte n;

  for (n = 8; n != 0; n--)
  {
    if ((d & 0x01) == 1)  // test least sig bit
    {
      digitalWrite(Pin, LOW);
      pinMode(Pin, OUTPUT);
      delayMicroseconds(5);
      pinMode(Pin, INPUT);
      delayMicroseconds(60);
    }
    else
    {
      digitalWrite(Pin, LOW);
      pinMode(Pin, OUTPUT);
      delayMicroseconds(60);
      pinMode(Pin, INPUT);
    }

    d = d >> 1; // now the next bit is in the least sig bit position.
  }

}

byte OneWireInByte(int Pin) // read byte, least sig byte first
{
  byte d, n, b;

  for (n = 0; n < 8; n++)
  {
    digitalWrite(Pin, LOW);
    pinMode(Pin, OUTPUT);
    delayMicroseconds(5);
    pinMode(Pin, INPUT);
    delayMicroseconds(5);
    b = digitalRead(Pin);
    delayMicroseconds(50);
    d = (d >> 1) | (b << 7); // shift d to right and insert b in most sig bit position
  }
  return (d);
}
