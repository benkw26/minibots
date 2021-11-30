void setup() {
  // put your setup code here, to run once:

}

void black(){
  
}

int counter = 0
void white(){
  int counter++;
  if(counter%2==1){
    turn_around_left();
  }
}

void blue(){
  motor1.drive();
  motor2.drive();
  delay(500);
}


void loop() {
  // put your main code here, to run repeatedly:
if(b<500){
  black();
}else if(c>8000){
  white();
}else{
  blue();
}
