#include <SparkFun_TB6612.h>
#include <HCSR04.h>
#include <Servo.h>
#include <Wire.h>
#include <LIDARLite.h>


#define AIN1 2
#define BIN1 7
#define AIN2 4
#define BIN2 8
#define PWMA 5
#define PWMB 6
#define STBY 9

const int offsetA = 1;
const int offsetB = 1;

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);
Servo servo;

void grab()
{
  
}

void drop()
{
  
}

void line_tracing()
{
  
}

void return1()
{
  
}

void detect_block()
{
  
}

void setup()
{
  servo.attach(A0);
}


void loop()
{
   
   delay(2000);
   //motor1.brake();
   //motor2.brake();
   //servo.write(90);
   //delay(2000);
   
   //servo.write(180);
}
