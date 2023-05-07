#include <Servo.h>

Servo myservo;
int ledPin = 2; // LED is connected to digital pin 2
int pos = 0; 

void setup() {
  myservo.attach(10); // Attach the servo to pin 10
  pinMode(ledPin, OUTPUT); // set the digital pin as output
  randomSeed(analogRead(0)); // initialize the random number generator
}

void loop() {
  int randNum = random(100); // generate a random number

  digitalWrite(ledPin, HIGH); // turn the LED on

  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);
    delay(randNum);
  }

  digitalWrite(ledPin, LOW); // turn the LED off

  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);
    delay(randNum);
}