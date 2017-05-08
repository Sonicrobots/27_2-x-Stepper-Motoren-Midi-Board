// Make a stepper follow the MIDI VALUE 
// The stepper will move at a constant speed
//
// Copyright (C) 20176 MORITZ SIMON GEIST moritz@sonicrobots.com
// V.01
// Complied with the Accelstepper Libary http://www.airspayce.com/mikem/arduino/AccelStepper/classAccelStepper.html#a3bc75bd6571b98a6177838ca81ac39ab
// Belongs to the board: 
// "2 x Servo Driver (Microstep)
// MIDI IN
// v.01 18.03.2017
// SONIC ROBOTS"
//
// Stepper Lines are at: 8, 9 and 10, 11 to be connected to a micro step modul

#include <AccelStepper.h>
// Define a stepper and the pins it will use

AccelStepper stepper(1, 9, 8); 
// AccelStepper stepper2(1, 10, 11); 


void setup()
{  
   stepper.setMaxSpeed(10000);
   stepper.setSpeed(50000);  
    
}

void loop()
{
  stepper.runSpeed();   
  stepper.setPinsInverted(true, false, false);
  stepper.runSpeed();   
  delay(1000);
  stepper.setPinsInverted(false, false, false);
  stepper.runSpeed();   
  delay(1000);
}
