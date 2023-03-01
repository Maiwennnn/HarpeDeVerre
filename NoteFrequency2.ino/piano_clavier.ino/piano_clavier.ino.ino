/*
  Physical Pixel

  An example of using the Arduino board to receive data from the computer. In
  this case, the Arduino boards turns on an LED when it receives the character
  'H', and turns off the LED when it receives the character 'L'.

  The data can be sent from the Arduino Serial Monitor, or another program like
  Processing (see code below), Flash (via a serial-net proxy), PD, or Max/MSP.

  The circuit:
  - LED connected from digital pin 13 to ground through 220 ohm resistor

  created 2006
  by David A. Mellis
  modified 30 Aug 2011
  by Tom Igoe and Scott Fitzgerald

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/PhysicalPixel
*/
#include <SerialFlash.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <C:\Program Files (x86)\Arduino\hardware\teensy\avr\libraries\SD\src\SD.h>
#include "glassHarp.h"
AudioOutputI2S         audioOutput; 
glassHarp gh1;

const int ledPin = 13; // the pin that the LED is attached to
int incomingByte;      // a variable to read incoming serial data into
float freq; 

AudioConnection patchCord1(gh1, 0, audioOutput, 0);
AudioConnection patchCord2(gh1, 0, audioOutput, 1);
AudioControlSGTL5000 audioShield;


void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  AudioMemory(2);
  audioShield.enable();
  audioShield.volume(0.6);
  // initialize the LED pin as an output:
}

void joueNote( float note){
  //joue = false;

  //joue = true; 
}

void loop() {
  // see if there's incoming serial data:
  if (Serial.available() > 0) {
    // read the oldest byte in the serial buffer:
    incomingByte = Serial.read();
    switch(incomingByte){
      case 'a':
        freq=261.6;
        break;
      case 'z':
        freq=277.2;
        break;
      case 'e':
        freq=293.7;
        break;
      case 'r':
        freq=311.1;
        break;
      case 't':
        freq=329.6;
        break;
      case 'y':
        freq=349.2;
        break;
      case 'u':
        freq=370;
        break;
      case 'i':
        freq=392;
        break;
      case 'o':
        freq=415.3;
        break;
      case 'p':
        freq=440;
        break;
      case '^':
        freq=466.2;
        break;
      case '$':
        freq=493.9;
        break;
         
    }
    

    
    Serial.write("On joue la note\n");    
    gh1.setParamValue("freq", freq);
    gh1.setParamValue("gate", 1);
    delay(1000);
    gh1.setParamValue("gate", 0);
    delay(50);
    Serial.print(incomingByte);
  }
}
