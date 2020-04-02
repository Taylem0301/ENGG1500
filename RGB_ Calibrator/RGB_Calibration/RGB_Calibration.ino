#include <SparkFun_APDS9960.h>


#define ECHO 12
#define TRIG 7

SparkFun_APDS9960 apds = SparkFun_APDS9960();
uint8_t proximity_data = 0;
unsigned int distance_mm = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(ECHO, INPUT); //Initialise ECHO as INPUT
  pinMode(TRIG, OUTPUT); //Initialise TRIG as OUTPUT
  Serial.begin (9600);


  if ( apds.init() ) {
    Serial.println(F("APDS-9960 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }


  if (!apds.setProximityGain(PGAIN_2X)) {
    Serial.println(F("Something went wrong trying to get PGAIN"));
  }

  if ( apds.enableProximitySensor(false) ) {
    Serial.println(F("Proximity sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during sensor init!"));
  }


}

void loop() {
  // put your main code here, to run repeatedly:


  Serial.println("time,APDS9960,HCSR04_mm");
  for (int i = 0; i < 100; ++i)
  {
    // Read the proximity value
    if ( !apds.readProximity(proximity_data) ) {
      Serial.println("Error reading proximity value");
      break;// breaks out of the for loop early
    }
    //Read ultrasonic data
    distance_mm = sonar_mm();
    //Print the CSV data
    Serial.print(i);
    Serial.print(",");
    Serial.print(proximity_data);
    Serial.print(",");
    Serial.println(distance_mm);
    // Wait 200 ms before next reading
    delay(200);
  }
  while (1) {}; //infinite loop to stop the experiment
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
