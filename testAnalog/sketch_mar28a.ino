#include <Servo.h>
Servo s1;

void setup() {
  s1.attach(23);
  Serial.begin(9600);
}

void loop() {
  int tmp = map(analogRead(15), 0, 1023, 0, 179) * 2 ;
  if (tmp != s1.read()) {
    s1.write(tmp); 
  }
  
}
