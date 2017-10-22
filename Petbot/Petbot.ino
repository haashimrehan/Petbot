#include <Servo.h>

Servo lServo;
Servo rServo;

const int trigPin = 2; //Ultrasonic Sensor
const int echoPin = 4; //Ports

int num;
long duration, cm;
void stopServos()             //Stops driving servos
{
  rServo.writeMicroseconds(1500);
  lServo.writeMicroseconds(1500);
}

void turnRight()              //Turns Right
{
  lServo.writeMicroseconds(1600);
  rServo.writeMicroseconds(1600);
}

void turnLeft()             //Turns Left
{
  lServo.writeMicroseconds(1400);
  rServo.writeMicroseconds(1400);
}

void forward()            //Drives forward
{
  rServo.writeMicroseconds(1400);
  lServo.writeMicroseconds(1600);
}
void reverse()            //Reverses
{
  rServo.writeMicroseconds(1600);
  lServo.writeMicroseconds(1400);
}
void rightCirc()        //drives in a circle to the right
{
  lServo.writeMicroseconds(1800);
  rServo.writeMicroseconds(1400);
}

void leftCirc()        //drives in a circle to the left
{
  lServo.writeMicroseconds(1400);
  rServo.writeMicroseconds(1800);
}

void pingSense()
{ //******Ping Sensor******//
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
  Serial.print(cm);     //print distance
  Serial.print("cm");
  Serial.println();
} //******Ping Sensor******//

void pingLeft()
{
  pingSense();
  forward();

  if (cm < 20)
  {
    reverse();
    delay(500);
    turnLeft();
  }
}

void pingRight()
{
  pingSense();
  forward();
  if (cm < 20)
  {
    reverse();
    delay(500);
    turnRight();
  }
}

void setup() {
  rServo.attach(9);  // attaches the servos
  lServo.attach(10);
  stopServos();
  Serial.begin(9600); //start Serial
  delay (5000);   //wait until main loop starts
}

void loop() {
  pingSense(); //Ping sensor detecting distance

  num = random(int(2));   //randomly choses between the two cases (0 and 1)
  switch (num) {
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
  }
  delay (1000);

}

long microsecondsToCentimeters(long microseconds) //Ultrasonic Conversion to cm
{
  return microseconds / 29 / 2;
}

