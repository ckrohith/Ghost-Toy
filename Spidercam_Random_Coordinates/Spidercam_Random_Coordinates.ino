#include <AccelStepper.h>
#include <MultiStepper.h>
#include <Ultrasonic.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Ultrasonic ultrasonic(A4, A5);
int distance=0;

AccelStepper stepper4(1, 2, 3); // (Typeof driver: with 2 pins, STEP, DIR)
AccelStepper stepper2(1, 4, 5);
AccelStepper stepper1(1, 6, 7);
AccelStepper stepper3(1, 8, 9);

MultiStepper steppersControl;  // Create instance of MultiStepper

int coordinate[] = {0, 0, 0};
int l1 = 78;
int l2 = 78;
int l3 = 78;
int l4 = 78;
long gotoposition[4]; // An array to store the target positions for each stepper motor

void setup() {
  Serial.begin(9600); // Starting Serial Terminal

  stepper1.setMaxSpeed(100); // Set maximum speed value for the stepper

  stepper2.setMaxSpeed(100);
  stepper3.setMaxSpeed(100);
  stepper4.setMaxSpeed(100);

  // Adding the 4 steppers to the steppersControl instance for multi stepper control
  steppersControl.addStepper(stepper1);
  steppersControl.addStepper(stepper2);
  steppersControl.addStepper(stepper3);
  steppersControl.addStepper(stepper4);
}

void loop() {
  delay(5000);

  distance = ultrasonic.read();
  Serial.print("Sensor Distance: ");
  Serial.println(distance);

  coordinate[0] = Random();
  coordinate[1] = Random();
  coordinate[2] = Random_height();

  Serial.print("Coordinate: ");
  Serial.print(coordinate[0]);
  Serial.print(", ");
  Serial.print(coordinate[1]);
  Serial.print(", ");
  Serial.print(coordinate[2]);
  Serial.println();

  Serial.print("Length of rope: ");
  Serial.print(l1);
  Serial.print(", ");
  Serial.print(l2);
  Serial.print(", ");
  Serial.print(l3);
  Serial.print(", ");
  Serial.print(l4);
  Serial.println();
  Serial.println();

  if (distance > 50) {
    gotoposition[0] = 100*(l1-sqrt(((46-coordinate[0])*(46-coordinate[0]))+((50-coordinate[1])*(50-coordinate[1]))+((40-coordinate[2])*(40-coordinate[2]))))/4;
    gotoposition[1] = 100*(l2-sqrt(((46-coordinate[0])*(46-coordinate[0]))+((-50-coordinate[1])*(-50-coordinate[1]))+((40-coordinate[2])*(40-coordinate[2]))))/4;
    gotoposition[2] = 100*(l3-sqrt(((-46-coordinate[0])*(-46-coordinate[0]))+((50-coordinate[1])*(50-coordinate[1]))+((40-coordinate[2])*(40-coordinate[2]))))/4;
    gotoposition[3] = 100*(l4-sqrt(((-46-coordinate[0])*(-46-coordinate[0]))+((-50-coordinate[1])*(-50-coordinate[1]))+((40-coordinate[2])*(40-coordinate[2]))))/4;

    steppersControl.moveTo(gotoposition); // Calculates the required speed for all motors
    steppersControl.runSpeedToPosition();

    l1 = sqrt(((46-coordinate[0])*(46-coordinate[0]))+((50-coordinate[1])*(50-coordinate[1]))+((40-coordinate[2])*(40-coordinate[2])));
    l2 = sqrt(((46-coordinate[0])*(46-coordinate[0]))+((-50-coordinate[1])*(-50-coordinate[1]))+((40-coordinate[2])*(40-coordinate[2])));
    l3 = sqrt(((-46-coordinate[0])*(-46-coordinate[0]))+((50-coordinate[1])*(50-coordinate[1]))+((40-coordinate[2])*(40-coordinate[2])));
    l4 = sqrt(((-46-coordinate[0])*(-46-coordinate[0]))+((-50-coordinate[1])*(-50-coordinate[1]))+((40-coordinate[2])*(40-coordinate[2])));
  }
}

int Random(){
  int num = rand()%40;
  return num;
}

int Random_height(){
  int num = rand()%10;
  return num;
}