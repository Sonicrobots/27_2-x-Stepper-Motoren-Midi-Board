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
#include <MIDI.h>
#include <midi_Defs.h>
#include <midi_Message.h>
#include <midi_Namespace.h>
#include <midi_Settings.h>
MIDI_CREATE_DEFAULT_INSTANCE();
int maxspeed = 100000;
// Define a stepper and the pins it will use

AccelStepper stepper1(1, 9, 8); 
AccelStepper stepper2(1, 10, 11); 

#define ANALOG_IN A0

// Readout the coded switch on PIN 2,3,4,7 on Startup. To set the MIDI Channel (1-16)
uint8_t readMidiChannel()
{
  // set pins as inputs
  pinMode(2, INPUT_PULLUP);pinMode(7, INPUT_PULLUP);pinMode(4, INPUT_PULLUP);pinMode(3, INPUT_PULLUP); // the pins for the coded channel switch with build in PULLUP resistors

  uint8_t i=0;
  bitWrite(i, 0, !digitalRead(3));
  bitWrite(i, 1, !digitalRead(7));
  bitWrite(i, 2, !digitalRead(2));
  bitWrite(i, 3, !digitalRead(4));

  return i+1; //+1 .. nullausgleich
}



void HandleNoteOn(byte channel, byte note, byte velocity) 
{
  
  if (channel == 1){
  
      if (note < 64) {
                      digitalWrite(13, HIGH);
                      int speedint = map(note, 1, 64, (maxspeed*0.01), maxspeed);
                      stepper1.setSpeed(speedint);  
                       stepper1.setPinsInverted(true, false, false);
                         //  stepper1.runSpeed();   
                      }
      
      if (note > 64) {
        digitalWrite(13, HIGH);
                      int speedint= map(note, 65, 127, (maxspeed*0.01), maxspeed);
                      stepper1.setSpeed(speedint);  
                      stepper1.setPinsInverted(false, false, false);
                       //   stepper1.runSpeed();   
                     } 
                    }

  if (channel == 2){
  
      if (note < 64) {
        digitalWrite(13, HIGH);
                      int speedint = map(note, 1, 64, (maxspeed*0.01), maxspeed);
                      stepper2.setSpeed(speedint);  
                       stepper2.setPinsInverted(true, false, false);
                           // stepper2.runSpeed();   
                      }
      
      if (note > 64) {
        digitalWrite(13, HIGH);
                      int speedint= map(note, 65, 127, (maxspeed*0.01), maxspeed);
                      stepper2.setSpeed(speedint);  
                      stepper2.setPinsInverted(false, false, false);
                              //                   stepper2.runSpeed();   
                     } 
                    }
}

void HandleNoteOff(byte channel, byte note, byte velocity) 
{
  digitalWrite(13, LOW);
  if (channel == 1)
  {
  stepper1.stop();
  }
  if (channel == 2)
  {
  stepper2.stop();
  }
  
}

///////////////
void setup()
{  
  
  pinMode(13, OUTPUT);
  stepper1.setMaxSpeed(100000);
  stepper1.setSpeed(0);  
  stepper2.setMaxSpeed(100000);
  stepper2.setSpeed(0);  
  
  // stepper.setAcceleration(5000);
  MIDI.setHandleNoteOn(HandleNoteOn);
  MIDI.setHandleNoteOff(HandleNoteOff);
  MIDI.begin(MIDI_CHANNEL_OMNI);  // ALL Channels
    
}

void loop()
{
    MIDI.read();
 stepper1.runSpeed();   
 stepper2.runSpeed();   
  
}
