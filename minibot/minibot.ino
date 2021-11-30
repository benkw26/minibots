#include <SparkFun_TB6612.h>
#include <HCSR04.h>
#include <Wire.h>
#include <LIDARLite.h>

//useful commands:


#define AIN1 2
#define BIN1 7
#define AIN2 4
#define BIN2 8
#define PWMA 5
#define PWMB 6
#define STBY 9

const int offsetA = 1;
const int offsetB = 1;
const int pingPin = 13; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 12; // Echo Pin of Ultrasonic Sensor

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);
LIDARLite myLidarLite;

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}

void forward(int duration)
{ 
  unsigned long initial_time = millis();
  motor1.drive(50);
  motor2.drive(208);
  delay(150);
  while((millis() - initial_time) < duration){
    if(is_robot() == false){
      motor1.drive(255);
      motor2.drive(208);
    }else{
      br();
      delay(500);
      forward(duration - (millis() - initial_time));
      
    }
  }
}

void turn_around_left(){
  motor1.drive(186);
  delay(1200);
  motor1.brake();
}

void turn_around_right(){
  motor2.drive(162);
  delay(1200);
  motor2.brake();
}

void left90(){
  motor1.drive(155);
  delay(800);
  motor1.brake();
}

void dumb_way(){
  forward(3000);
  left90();
  forward(1500);
  for(int i = 0; i < 8; i++){
    if((i % 2) == 0){
      turn_around_left();
      forward(3000);
    }else{
      turn_around_right();
      forward(3000);
    }
  }
  turn_around_left();
  forward(1500);

  
}

void br()
{
  motor1.brake();
  motor2.brake();
}

void spiral(int t)
{
  motor1.drive(186);
  motor2.drive(50);
  delay(t);
}

float distance_sonic(){
   long duration, inches, cm;
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   duration = pulseIn(echoPin, HIGH);
   return microsecondsToCentimeters(duration);
}

int distance_laser()
{
  if(!digitalRead(3)){
    return(myLidarLite.distanceContinuous());
  }else{
    return distance_laser();
  }
}

bool is_robot(){
  if(distance_sonic() < 10){
    return true;
  }else{
    return false;
  }
}

void detect_block()
{
  
}

void setup()
{
  Serial.begin(115200);
  
  myLidarLite.begin();
  myLidarLite.beginContinuous();
  pinMode(3, INPUT);
  pinMode(pingPin, OUTPUT);
  pinMode(echoPin, INPUT);
}


void loop()
{ 
//  if(distance_sonic() < 5){
//    dumb_way();
//    delay(5000);
//  }
   forward(10000);

}
