
const int x_pin = 0;
const int y_pin = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 Serial.print("X-Axis: ");
 Serial.print(analogRead(x_pin));
 Serial.print("\n");
 Serial.print("Y-Axis: ");
 Serial.print(analogRead(y_pin));
 Serial.print("\n\n");
 delay(500);
}
