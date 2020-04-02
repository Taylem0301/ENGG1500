float x1; // value of how far sensor is from centreline of the chassis. Is a constant.
float x2;
float x3;
float x4;

float w1; //analog value given from sensor
float w2;
float w3;
float w4;

float den = 0; //used for calculations
float num = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
   w1 = analogRead(A0);
   w2 = analogRead(A1);
   w3 = analogRead(A2);
   w4 = analogRead(A3);
   num = (x1*w1)+(x2*w2)+(x3*w3)+(w4*x4);
   den = w1+w2+w3+w4;

   float lineDist = num/den;

   Serial.print("Distance from line = ");
   Serial.println(lineDist);
   delay(50);
}
