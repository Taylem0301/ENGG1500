#define ECHO 12
#define TRIG 7

void setup() {
  // put your setup code here, to run once:
  pinMode(5,OUTPUT);  //ENA (Left Motor) (0-255 Speed Range)
  pinMode(6,OUTPUT);  //ENB (Right Motor)
  pinMode(8,OUTPUT);  //IN1 (Left Wheel Back)
  pinMode(9,OUTPUT);  //IN2 (Left Wheel Forward)
  pinMode(10,OUTPUT); //IN3 (Right Wheel Back)
  pinMode(11,OUTPUT); //IN4 (Right Wheel Forward)
  pinMode(A0,INPUT); //IR sensor
  delay(2000); //delay before loop
  //TEST CODE FOR Change detection
  
  pinMode(ECHO,INPUT); //Initialise ECHO as INPUT
  pinMode(TRIG,OUTPUT); //Initialise TRIG as OUTPUT
  Serial.begin(9600); //Begin Serial Communication
}

void loop() {
  rightForwards();
  leftForwards();

  wallFind();
  

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

unsigned int sonar_mm(void){
  long duration = 0;
  const float speed_sound = 340.29; //assigns speed_sound the constant float of 340.29 which saves memory

  digitalWrite(TRIG,HIGH); //emitting ultrasonic pulse
  delayMicroseconds(10);
  digitalWrite(TRIG,LOW);

  duration = pulseIn(ECHO,HIGH); //gives the width in microseconds

  return (unsigned int)(0.5 * duration * 1e-6 * speed_sound * 1e3); //(.5, half distance)
  //(1e-6, seconds to microseconds)(1e3, metres to millimetres)
}

void wallFind(void){
  while(sonar_mm < 300){  //While more than 300mm away from wall move forward
    analogWrite(5,100);
    analogWrite(6,100);
}
  analogWrite(5,0);        //Stop once closer than 300mm to the wall
  analogWrite(6,0);
}

void followWall(void){
  // turn closer when > 500mm
  // turn further away < 250mm

  //find the point at which the speaker gets the shortest distnace
  //turn the speaker and the robot 90o
  // speaker should be poimting at the corner robot at random angle going counter/clockwise around
  //speaker should stay pointed at corner
  



  
}

void boxDetection(void){
  // when black surface detected stop 
  //if no black surface detected keep going


  
}
