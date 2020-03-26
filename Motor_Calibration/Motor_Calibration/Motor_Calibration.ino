
#include <ENGG1500Lib.h>

void setup() {
  // put your setup code here, to run once:
  pinMode(5, OUTPUT); //ENA (Left Motor) (0-255 Speed Range)
  pinMode(6, OUTPUT); //ENB (Right Motor)
  pinMode(8, OUTPUT); //IN1 (Left Wheel Back)
  pinMode(9, OUTPUT); //IN2 (Left Wheel Forward)
  pinMode(10, OUTPUT); //IN3 (Right Wheel Back)
  pinMode(11, OUTPUT); //IN4 (Right Wheel Forward)
  enc_init();
  delay(2000);
  Serial.begin(9600);
  Serial.println("PWM,ENC_L,ENC_R");

  
}

void loop() {
  // put your main code here, to run repeatedly:  
  int x = 0;
  leftForwards();
  rightForwards();
  
  for (x = 0; x<256; x++){
    enc_clear();
    analogWrite(5,x);
    analogWrite(6,x);
    delay(1000);
    Serial.print(x);
    Serial.print(",");
    Serial.print(enc_getLeft());
    Serial.print(",");
    Serial.println(enc_getRight());
    
  }
} 

void leftForwards(void) {
  //sets left wheel to move forward
  digitalWrite(8, LOW); //IN1
  digitalWrite(9, HIGH); //IN2
}


void leftBackwards(void) {
  //sets left wheel to move backwards
  digitalWrite(8, HIGH); //IN1
  digitalWrite(9, LOW); //IN2
}

void rightForwards(void) {
  //sets right wheel to move forwards
  digitalWrite(10, LOW); //IN3
  digitalWrite(11, HIGH); //IN4
}

void rightBackwards(void) {
  //sets right wheel to move backwards
  digitalWrite(10, HIGH); //IN3
  digitalWrite(11, LOW); //IN4
}
