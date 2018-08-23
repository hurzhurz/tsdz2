#include <SoftwareSerial.h>

SoftwareSerial SerialM(9, 7); // RX, TX(ignore)
SoftwareSerial SerialD(8, 7); // RX, TX(ignore)

unsigned long last_serial_switch;

uint8_t F_chk_8( uint8_t bval, uint8_t cval ) {
    return ( bval + cval ) % 256;
}


#define BUFFERLEN 20
uint8_t BUFFER[BUFFERLEN];
uint8_t BUFFERPOS=0;

void buffer_clear()
{
  for(uint8_t i=0;i<BUFFERLEN;i++)
    BUFFER[i]=0x00;
}
uint8_t buffer_pos(uint8_t pos)
{
  while(pos>=BUFFERLEN)
    pos-=BUFFERLEN;
  return pos;
}
void buffer_add(uint8_t data)
{
  BUFFER[BUFFERPOS]=data;
  BUFFERPOS=buffer_pos(BUFFERPOS+1);
}




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SerialM.begin(9600);
  SerialD.begin(9600);
  SerialM.listen();
  last_serial_switch=millis();
  buffer_clear();
}

int8_t FindPaket(uint8_t start, uint8_t len)
{
  for(uint8_t i=0;i<BUFFERLEN;i++)
  {
    if(BUFFER[i]==start)
    {
      uint8_t chk=0;
      for(uint8_t ii=0;ii<(len-1);ii++)
      {
        chk=F_chk_8(BUFFER[buffer_pos(i+ii)],chk);
      }
      if(chk==BUFFER[buffer_pos(i+len-1)])
      {
        //Serial.println("found!");
        return (int8_t)i;
      }
    }
  }
  return -1;
}

void PrintPaket(uint8_t pos, uint8_t len)
{
  for(uint8_t i=0;i<len;i++)
  {
    Serial.print(BUFFER[buffer_pos(pos+i)],HEX);
    Serial.print(" ");
  }
}

void SwitchSerial()
{
  if(SerialM.isListening())
    SerialD.listen();
  else
    SerialM.listen();
  buffer_clear();
  last_serial_switch=millis();
  //Serial.println("switch");
}
void TimeoutSwitchSerial(unsigned int timeout)
{
  if( (millis()-last_serial_switch) > timeout )
  {
    //Serial.println("timeout");
    SwitchSerial();
  }
}
void ReadSerial()
{
  int8_t p;
  while(SerialM.available())
  {
    buffer_add(SerialM.read());
    if((p = FindPaket(0x43,9)) > -1)
    {
       Serial.print("Motor: ");
       PrintPaket(p,9);
       Serial.println("");
       SwitchSerial();
    }
  }
  
  while(SerialD.available())
  {
    buffer_add(SerialD.read());
    if((p = FindPaket(0x59,7)) > -1)
    {
       Serial.print("LCD: ");
       PrintPaket(p,7);
       Serial.println("");
       SwitchSerial();
    }
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:

  ReadSerial();
  TimeoutSwitchSerial(250);
}
