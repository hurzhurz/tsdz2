#include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 11); // RX, TX

unsigned long time;
float kmh = 8;
float wheel = 28.0;
bool offdelay = false;
unsigned int interval;
  
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  mySerial.begin(9600);
  time=millis();
  
  pinMode(6, OUTPUT);
  digitalWrite(6, HIGH);
  wheel=wheel*2.54*3.14159; // cm
  kmh=(kmh/3.6)*100.0; // cm/s
  interval = (unsigned int) (1000.0/(kmh/wheel));

  Serial.println(interval);
  Serial.println((kmh/wheel));
}

void loop() { // run over and over
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  
  if((millis()-time)> interval )
  {
    time=millis();
    digitalWrite(6, LOW);
    offdelay=true;
  }
  if(offdelay && (millis()-time)> 5)
  {
    digitalWrite(6, HIGH);
    offdelay=false;
  }

}