#include <SparkFun_TB6612.h>
#include <HCSR04.h>
#include <Wire.h>
#include <LIDARLite.h>
#include "Adafruit_TCS34725.h"

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

uint16_t r, g, b, c;

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);
LIDARLite myLidarLite;
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X);

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}

int forward(int duration)
{ 
  long initial_time = millis();
  if(is_robot() == false){
    motor1.drive(50);
    motor2.drive(150);
    delay(25);
  }
  while((millis() - initial_time) < duration){
    //Serial.println((millis() - initial_time));
    if(is_robot() == false){
      motor1.drive(255);
      motor2.drive(208);
    }else{
      br();
      delay(2000);
      Serial.println(duration);
      Serial.println(millis() - initial_time);
      Serial.println(duration + 2150 - (millis() - initial_time));
      forward(duration + 2003 - (millis() - initial_time));
      
    }
  }
  br();
  return 0;
}

void turn_around_left(){
  motor1.drive(210);
  delay(1200);
  motor1.brake();
}

void turn_around_right(){
  motor2.drive(150);
  delay(1000);
  motor2.brake();
}

void left90(){
  motor1.drive(155);
  delay(1150);
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
  spiral(1000000);
  
}

void br()
{
  Serial.println("brake");
  motor1.brake();
  motor2.brake();
}

void spiral(int t=0)
{
  unsigned long long startMillis = millis();
  unsigned long long currentMillis = millis();
  unsigned long long dMillis = currentMillis-startMillis;
  
  while (dMillis < t || t == 0) {
    currentMillis = millis();
    dMillis = currentMillis-startMillis;
    motor1.drive(240); //to 208
    int spd = floor(75*pow(1.05,floor(dMillis/1000)));
    if(spd>200){
      spd = 200;
    }
    motor2.drive(spd);

//    if(color() == 1){
//      left90();
//    }
    
    if(color() == 2) {
      break;
    }
  }
  br();
  delay(10000000);
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
  if(distance_sonic() < 30){
    return true;
  }else{
    return false;
  }
}

int color(){
  tcs.getRawData(&r, &g, &b, &c);
  if(c > 200){
    Serial.println("WHITE");
    return 1;
  }else if(((double) b) / ((double)c) >= 0.35){
    Serial.println("BLUE");
    return 2; //blue
  }else{
    return 0;
  }
}

void setup(){
  Serial.begin(115200);
  myLidarLite.begin();
  myLidarLite.beginContinuous();
  pinMode(3, INPUT);
  pinMode(pingPin, OUTPUT);
  pinMode(echoPin, INPUT);
  tcs.begin();
}


void loop(){ 
  dumb_way();
}
