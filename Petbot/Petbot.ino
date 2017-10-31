#include <Servo.h>

Servo lServo;
Servo rServo;

const int trigPin = 2; //Ultrasonic Sensor
const int echoPin = 4; //Ports

int num1;
long duration, cm;

void stopServos() //Stops driving servos
{
  rServo.writeMicroseconds(1500);
  lServo.writeMicroseconds(1500);
}

void turnRight() //Turns Right
{
  lServo.writeMicroseconds(1600);
  rServo.writeMicroseconds(1600);
}

void turnRight90() {
  turnRight();
  delay(800);
  stopServos();
}

void turnLeft() //Turns Left
{
  lServo.writeMicroseconds(1400);
  rServo.writeMicroseconds(1400);
}

void turnLeft90() {
  turnLeft();
  delay(900);
  stopServos();
}

void forward() //Drives forward
{
  rServo.writeMicroseconds(1400);
  lServo.writeMicroseconds(1600);
}
void reverse() //Reverses
{
  rServo.writeMicroseconds(1600);
  lServo.writeMicroseconds(1400);
}
void rightCirc() //drives in a circle to the right
{
  lServo.writeMicroseconds(1800);
  rServo.writeMicroseconds(1400);
}

void leftCirc() //drives in a circle to the left
{
  lServo.writeMicroseconds(1400);
  rServo.writeMicroseconds(1800);
}

void lCircles() {
  pingSense();
  if (cm < 15) {
    reverse();
    delay(600);
    lServo.writeMicroseconds(1650);
    rServo.writeMicroseconds(1650);
    delay(1500);
  }
}

void rCircles() {
  lServo.writeMicroseconds(1350);
  rServo.writeMicroseconds(1350);
}

void pingSense() { //******Ping Sensor******//
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);
  Serial.print(cm); //print distance
  Serial.print("cm");
  Serial.println();
} //******Ping Sensor******//

void pingLeft() {
  pingSense();
  forward();

  if (cm < 15) {
    reverse();
    delay(500);
    turnLeft90();
    delay(200);
  }
}

void pingRight() {
  pingSense();
  forward();
  if (cm < 15) {
    reverse();
    delay(500);
    turnRight90();
    delay(200);
  }
}

void setup() {
  rServo.attach(9); // attaches the servos
  lServo.attach(10);
  stopServos();
  Serial.begin(9600); //start Serial
  delay(5000); //wait until main loop starts
}

void loop() {
    for (int k = 0; k < 100; k++) {
     forward();
     pingSense(); //Ping sensor detecting distance
     num1 = random(int(3));   //randomly choses between the three cases
     switch (num1) {
       case 0:
         for (int i = 0; i < 2; i++) { //Reverses then turns left. does this twice
           pingLeft();
         }
         break;
       case 1:
         for (int j = 0; j < 2; j++) {   //Reverses then turns left. does this twice
           pingRight();
         }
         break;
       case 2:
         lCircles();
         break;
     }
    }

    delay (1000);

}

long microsecondsToCentimeters(long microseconds) //Ultrasonic Conversion to cm
{
  return microseconds / 29 / 2;
}
