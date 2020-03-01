// GLOBAL VARIABLES
const int printSerial = 0;
const int printLCD = 0;
const int lightThreshold = 600;
const int timestep = 10;

// MOTORS
int left1a = 13;
int left1b = 12;
int left1speed = 11;
int left2speed = 10;
int left2a = 9;
int left2b = 8;

int right1a = 7;
int right1b = 6;
int right1speed = 5;
int right2speed = 3;
int right2a = 4;
int right2b = 2;

int motorPower = 70;

// IR SENSORS 
int leftSensor = A1;
int rightSensor = A0;
int leftReading = 0;
int rightReading = 0;

void setup(){
  if(printSerial){Serial.begin(9600);}
}

void walkForward(int delayTime = 0){
  digitalWrite(left1a,HIGH);
  digitalWrite(left1b,LOW);  
  analogWrite(left1speed,motorPower);
  digitalWrite(left2a,LOW);
  digitalWrite(left2b,HIGH);  
  analogWrite(left2speed,motorPower);
  digitalWrite(right1a,LOW);
  digitalWrite(right1b,HIGH);  
  analogWrite(right1speed,motorPower);
  digitalWrite(right2a,HIGH);
  digitalWrite(right2b,LOW);  
  analogWrite(right2speed,motorPower);
  delay(delayTime);
}

void turnLeft(int delayTime = 0){
  digitalWrite(left1a,LOW);
  digitalWrite(left1b,HIGH);  
  analogWrite(left1speed,motorPower);
  digitalWrite(left2a,HIGH);
  digitalWrite(left2b,LOW);  
  analogWrite(left2speed,motorPower);
  digitalWrite(right1a,LOW);
  digitalWrite(right1b,HIGH);  
  analogWrite(right1speed,motorPower);
  digitalWrite(right2a,HIGH);
  digitalWrite(right2b,LOW);  
  analogWrite(right2speed,motorPower);  
  delay(delayTime);
}

void turnRight(int delayTime = 0){
  digitalWrite(left1a,HIGH);
  digitalWrite(left1b,LOW);  
  analogWrite(left1speed,motorPower);
  digitalWrite(left2a,LOW);
  digitalWrite(left2b,HIGH);  
  analogWrite(left2speed,motorPower);
  digitalWrite(right1a,HIGH);
  digitalWrite(right1b,LOW);  
  analogWrite(right1speed,motorPower);
  digitalWrite(right2a,LOW);
  digitalWrite(right2b,HIGH);  
  analogWrite(right2speed,motorPower);
  delay(delayTime);
}

void walkBackwards(int delayTime = 0){
  digitalWrite(left1a,LOW);
  digitalWrite(left1b,HIGH);  
  analogWrite(left1speed,motorPower);
  digitalWrite(left2a,HIGH);
  digitalWrite(left2b,LOW);  
  analogWrite(left2speed,motorPower);
  digitalWrite(right1a,HIGH);
  digitalWrite(right1b,LOW);  
  analogWrite(right1speed,motorPower);
  digitalWrite(right2a,LOW);
  digitalWrite(right2b,HIGH);  
  analogWrite(right2speed,motorPower);
  delay(delayTime);
}

void stopMotors(int delayTime = 0){
  digitalWrite(left1a,LOW);
  digitalWrite(left1b,LOW);  
  analogWrite(left1speed,motorPower);
  digitalWrite(left2a,LOW);
  digitalWrite(left2b,LOW);  
  analogWrite(left2speed,motorPower);
  digitalWrite(right1a,LOW);
  digitalWrite(right1b,LOW);  
  analogWrite(right1speed,motorPower);
  digitalWrite(right2a,LOW);
  digitalWrite(right2b,LOW);  
  analogWrite(right2speed,motorPower);
  delay(delayTime);
}

void brakeMotors(int delayTime = 0){  
  digitalWrite(left1a,HIGH);
  digitalWrite(left1b,HIGH);  
  analogWrite(left1speed,motorPower);
  digitalWrite(left2a,HIGH);
  digitalWrite(left2b,HIGH);  
  analogWrite(left2speed,motorPower);
  digitalWrite(right1a,HIGH);
  digitalWrite(right1b,HIGH);  
  analogWrite(right1speed,motorPower);
  digitalWrite(right2a,HIGH);
  digitalWrite(right2b,HIGH);  
  analogWrite(right2speed,motorPower);
  delay(delayTime);
}

void getSensorData(){
  leftReading = analogRead(leftSensor);
  rightReading = analogRead(rightSensor);  
  if(printSerial){
    Serial.print(" LEFT = ");
    Serial.print(leftReading);
    Serial.print(" RIGHT = ");
    Serial.println(rightReading);
  }
  if(printLCD){
    // TODO
  }
}

void followLine(){  
  getSensorData();
  if(leftReading>lightThreshold){ //left black
    if(rightReading>lightThreshold){ // both black
      walkForward(timestep);
    }
    else{ // only left black
      walkBackwards(timestep);
      turnLeft(timestep);
    }
  }
  else{
    if(rightReading>lightThreshold){ //only right black
      walkBackwards(timestep);
      turnRight(timestep);
    }
    else{ // none black
      walkForward(timestep);
    }
  }
  stopMotors();
  delay(1);
}

void loop() {
  followLine();
}
