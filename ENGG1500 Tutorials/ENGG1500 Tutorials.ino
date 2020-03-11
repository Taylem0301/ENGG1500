void setup() {
  // put your setup code here, to run once:
  //setting outputs
  pinMode(5,OUTPUT);  //ENA (Left Motor)
  pinMode(6,OUTPUT);  //ENB (Right Motor)
  pinMode(8,OUTPUT);  //IN1 (Left Wheel Back)
  pinMode(9,OUTPUT);  //IN2 (Left Wheel Forward)
  pinMode(10,OUTPUT); //IN3 (Right Wheel Back)
  pinMode(11,OUTPUT); //IN4 (Right Wheel Forward)
  pinMode(A0,INPUT); //IR sensor
  delay(2000); //delay before loop
  //TEST CODE FOR Change detection
}

void loop() {
  // put your main code here, to run repeatedly:
  // Sets direction of wheel spin
  leftForwards();
  rightForwards();

  int sensorVal = digitalRead(A0);  //1 if no obstacle, 0 if none

  //causes wheels to move forward (Speed is a range between 0-255)
  analogWrite(5,sensorVal*100); //set left wheel to half speed if no obstacle detected
  analogWrite(6,sensorVal*100); //set right wheel to half speedif no obstacle detected
  
  
}

void leftForwards(void){
  //sets left wheel to move forward
  digitalWrite(8,LOW); //IN1
  digitalWrite(9,HIGH); //IN2
}


void leftBackwards(void){
  //sets left wheel to move backwards
  digitalWrite(8,HIGH); //IN1
  digitalWrite(9,LOW); //IN2
}

void rightForwards(void){
  //sets right wheel to move forwards
  digitalWrite(10,LOW); //IN3
  digitalWrite(11,HIGH); //IN4
}

void rightBackwards(void){
  //sets right wheel to move backwards
  digitalWrite(10,HIGH); //IN3
  digitalWrite(11,LOW); //IN4
}
