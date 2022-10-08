#define leftIR A2
#define rightIR A3

#include <Servo.h>
Servo myservo;


void setup() {
  // put your setup code here, to run once:
  myservo.attach(5);
  myservo.write(90);// move servos to center position -> 90°
  pinMode(leftIR, INPUT);
  pinMode(rightIR, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  myservo.write(0);// move servos to center position -> 90°
  delay(500);
  myservo.write(180);
  delay(500000);
  Serial.print("\nLeft:");
  Serial.print(digitalRead(leftIR));
  Serial.print("\nRight:");
  Serial.print(digitalRead(rightIR));
  delay(1000);
}
