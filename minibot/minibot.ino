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

void forward(int t)
{ 
  motor1.drive(255);
  motor2.drive(208);
  delay(t);
  br();
}

void center()
{
  forward(3000);
}

void turn_around_left(){
  motor1.drive(232);
  delay(1000);
  motor1.brake();
}

void turn_around_right(){
  motor2.drive(208);
  delay(1000);
  motor2.brake();
}

void left90(){
  motor1.drive(200);
  delay(1000);
  motor1.brake();
}

//void dumb_way(){
//  center();
//  left90();
//  forward();
//  for(int i = 0; i < 8; i++){
//    if((i % 2) == 0){
//      turn_around_left();
//      forward();
//    }else{
//      turn_around_right();
//      forward();
//    }
//  }
//  turn_around_left();
//  forward();
//
//  
//}

void sweep()
{
  
}

void rotate()
{
  
}

void br()
{
  motor1.brake();
  motor2.brake();
}

void return1()
{
  
}

float distance_sonic(){
   long duration, inches, cm;
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
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

void is_robot(){
 
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
}


void loop()
{   
  //forward(2000);
  //delay(5000);
  
// turn_around_left();
// delay(2000);
// turn_around_right();
// delay(2000);
  Serial.println(distance_sonic());
  delay(1000);

}
