#include <SoftwareSerial.h>

SoftwareSerial SerialD(8, 7); // RX, TX

uint8_t F_chk_8( uint8_t bval, uint8_t cval ) {
    return ( bval + cval ) % 256;
}

unsigned long last;
unsigned int interval = (1000/15); // message interval in ms

uint8_t message[9] = {0x43,0x02,0x01,0x51,0x51,0x00,0x1D,0x00,0x00}; // last byte is checksum that will be replaced
uint8_t msg_len = 9;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SerialD.begin(9600);
  last=millis();

  uint8_t chk=0;
  for(uint8_t i=0;i<(msg_len-1);i++)
  {
    chk=F_chk_8(message[i],chk);
  }
  message[msg_len-1]=chk;
  for(uint8_t i=0;i<msg_len;i++)
  {
    Serial.print(message[i],HEX);
    Serial.print(" ");
  }
  Serial.println("");
}

void loop() {
  // put your main code here, to run repeatedly:
  if((millis()-last)>interval)
  {
    last=millis();
    Serial.println("send");
    for(uint8_t i=0;i<msg_len;i++)
    {
      SerialD.write(message[i]);
    }
  }
}