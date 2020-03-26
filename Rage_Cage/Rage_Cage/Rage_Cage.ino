#include <ENGG1500Lib.h>
#include <Servo.h>


#define ECHO 12
#define TRIG 7

Servo fwdServo;

int i = 0;
int servoPos = 0;
int cornerCount = 0;
unsigned int distance_mm = 0;
int shortTrackCount = 0;
int y = 1;
int h = 1;
int angleCount = 0;
int shortAngleCount = 0;
int angleToWall;
int wallOrient = 0;
int activation = 0;
int incrementClicks;
int orientClicks;
int boxDetect;
int ShortCount;



void setup() {
  // put your setup code here, to run once:
  pinMode(5, OUTPUT); //ENA (Left Motor) (0-255 Speed Range)
  pinMode(6, OUTPUT); //ENB (Right Motor)
  pinMode(8, OUTPUT); //IN1 (Left Wheel Back)
  pinMode(9, OUTPUT); //IN2 (Left Wheel Forward)
  pinMode(10, OUTPUT); //IN3 (Right Wheel Back)
  pinMode(11, OUTPUT); //IN4 (Right Wheel Forward)
  pinMode(A0, INPUT); //IR vertical sensor
  pinMode(A5, INPUT);// IR Horizontal Sensor
  //delay before loop
  //TEST CODE FOR Change detection

  pinMode(ECHO, INPUT); //Initialise ECHO as INPUT
  pinMode(TRIG, OUTPUT); //Initialise TRIG as OUTPUT
  Serial.begin(9600); //Begin Serial Communication

  fwdServo.attach(13);
  enc_init();

  delay(2000);
}



void loop() {

  wallFind();
  while (wallOrient < 3) {
    cornerDetection();
    WallOrientation();
  }
   
  followWall();



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




unsigned int sonar_mm_wallFind(void) {
  long duration = 0;
  const float speed_sound = 340.29; //assigns speed_sound the constant float of 340.29 which saves memory

  digitalWrite(TRIG, HIGH); //emitting ultrasonic pulse
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH); //gives the width in microseconds

  return (unsigned int)(0.5 * duration * 1e-6 * speed_sound * 1e3); //(.5, half distance)
  //(1e-6, seconds to microseconds)(1e3, metres to millimetres)
}



unsigned int sonar_mm_cornerDetection(void) {
  long duration = 0;
  const float speed_sound = 340.29; //assigns speed_sound the constant float of 340.29 which saves memory

  digitalWrite(TRIG, HIGH); //emitting ultrasonic pulse
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH); //gives the width in microseconds

  return (unsigned int)(0.5 * duration * 1e-6 * speed_sound * 1e3); //(.5, half distance)
  //(1e-6, seconds to microseconds)(1e3, metres to millimetres)
}





void wallFind(void) {
  rightForwards();
  leftForwards();

  fwdServo.write(90);

  while (sonar_mm_wallFind() > 140) { //While more than 300mm away from wall move forward
    analogWrite(5, 100);
    analogWrite(6, 100);
  }
  analogWrite(5, 0);       //Stop once closer than 300mm to the wall
  analogWrite(6, 0);
  delay(500);
}




void followWall(void) {
  // turn closer when > 500mm
  // turn further away < 250mm

  //find the point at which the speaker gets the shortest distnace
  //turn the speaker and the robot 90o
  // speaker should be poimting at the corner robot at random angle going counter/clockwise around
  //speaker should stay pointed at corner
  leftForwards();
  rightForwards();

  fwdServo.write(180);
  delay(500);

  int wallDistance = sonar_mm;
  int tackClicks;
  Serial.println(wallDistance);
  delay(100);
  
  if (wallDistance < 250) {
    enc_clear();
    leftForwards();
    rightBackwards();

    tackClicks = 5;
    incrementClicks = 0;
    while (incrementClicks < tackClicks) { //rotating to be parallel with wall
      while (enc_getLeft() < 1) {
        analogWrite(5, 200);
        analogWrite(6, 200);
      }
      analogWrite(5, 0);
      analogWrite(6, 0);
      delay(300);
      enc_clear();
      incrementClicks++;

    }
    analogWrite(5, 100);
    analogWrite(6, 100);
  }
  else if (wallDistance > 500) {
    enc_clear();
    leftBackwards();
    rightForwards();

    tackClicks = 5;
    incrementClicks = 0;

    while (incrementClicks < tackClicks) { //rotating to be parallel with wall
      while (enc_getLeft() < 1) {
        analogWrite(5, 200);
        analogWrite(6, 200);
      }
      analogWrite(5, 0);
      analogWrite(6, 0);
      delay(300);
      enc_clear();
      incrementClicks++;

    }
    analogWrite(5, 100);
    analogWrite(6, 100);
  }
  else {
    leftForwards();
    rightForwards();
    
    analogWrite(5,100);
    analogWrite(6,100);
  }
}


unsigned int sonar_mm(void) {
  long duration = 0;
  const float speed_sound = 340.29; //assigns speed_sound the constant float of 340.29 which saves memory

  digitalWrite(TRIG, HIGH); //emitting ultrasonic pulse
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH); //gives the width in microseconds

  return (unsigned int)(0.5 * duration * 1e-6 * speed_sound * 1e3); //(.5, half distance)
  //(1e-6, seconds to microseconds)(1e3, metres to millimetres)
}




void boxDetection(void) {
  // when black surface detected stop
  //if no black surface detected keep going

  delay(50);
  int sensorReading = analogRead(A0);
  Serial.println(sensorReading);
  if (sensorReading > 100) {
    boxDetect = 1;
  }
  else {
    boxDetect = 0;
  }
}





void cornerDetection(void) {
  int fwdServoPos = 0;
  int wallDis[20];
  cornerCount = 0;
  shortTrackCount = 0;
  shortAngleCount = 0;


  while (cornerCount < 20) {
    fwdServo.write(fwdServoPos);
    delay(100);
    wallDis[cornerCount] = sonar_mm_cornerDetection(); //find how far awy the wall is at 20 points
    fwdServoPos = fwdServoPos + 9;
    //Serial.println(wallDis[cornerCount]);
    cornerCount++;
  }



  int newTrack = 0;
  int shortTrack = wallDis[0];          //could be this line
  while (shortTrackCount < 20) {
    newTrack = wallDis[shortTrackCount];
    shortTrackCount++;
    if (newTrack < shortTrack) {
      shortTrack = newTrack;
    }
  }
  int compareAngle = 0;

  while (shortAngleCount == 0) {
    compareAngle = wallDis[angleCount]; //find the angle to orient towards the closest wall
    if (compareAngle == shortTrack) {
      shortAngleCount = 1;
    }
    else {
      angleCount = angleCount + 1;
    }
  }
  angleToWall = 9 * angleCount;
  fwdServo.write(angleToWall);
  //Serial.println(angleToWall);


}





void WallOrientation(void) {
  enc_clear();
  leftForwards();
  rightBackwards();

  orientClicks =  (180 - angleToWall) / 6;
  incrementClicks = 0;
  while (incrementClicks < orientClicks) { //rotating to be parallel with wall
    while (enc_getLeft() < 1) {
      analogWrite(5, 200);
      analogWrite(6, 200);
    }
    analogWrite(5, 0);
    analogWrite(6, 0);
    delay(300);
    enc_clear();
    incrementClicks++;

  }
  delay(500);
  wallOrient++;

}


/*
  void WalltoAngle(void) {
  int ServoPosition = 0;
  int counter = 0;
  int distance;
  int shortestTrack = 1000;

  while (counter < 10) {
    fwdServo.write(ServoPosition);
    sonar_mm_cornerDetection();
    delay(50);
    distance = sonar_mm_cornerDetection();
    if (distance < shortestTrack) {
      shortestTrack = distance;
      ShortCount = counter;
    }
    counter++;
    ServoPosition = ServoPosition + 18;
    fwdServo.write(ServoPosition);
    delay(100);
    Serial.println(distance);
    Serial.println(shortestTrack);
    Serial.println(ShortCount);
  }
  }
*/
