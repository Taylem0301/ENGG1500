#include <Servo.h>

Servo myservo;

int pos = 0;

void setup() {
  // put your setup code here, to run once:
  myservo.attach(13);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(pos != 180){
    pos = 180;
    myservo.write(pos);
    delay(500);
  }
  else{
    pos = 0;
    myservo.write(pos);
    delay(500);
  }
} 
