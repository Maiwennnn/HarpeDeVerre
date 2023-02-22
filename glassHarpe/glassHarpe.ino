#include <Audio.h>
#include "glassHarp.h"

glassHarp gh;
AudioInputI2S in;
AudioOutputI2S out;
AudioControlSGTL5000 audioShield;
AudioConnection patchCord0(in,0,gh,0);
AudioConnection patchCord1(in,1,gh,1);
AudioConnection patchCord2(gh,0,out,0);
AudioConnection patchCord3(gh,1,out,1);
float notes []={261.6,277.2,293.7,311.1,329.6,349.2,370.0,392.0,415.3,440.0,466.2,493.9}; 
int i=0; 

void setup() {
  AudioMemory(6);
  audioShield.enable();
  audioShield.inputSelect(AUDIO_INPUT_MIC);
  audioShield.micGain(10); // in dB
  audioShield.volume(0.5);
  gh.setParamValue("freq", 300);
}

void loop() {
  gh.setParamValue("freq", notes[i]);
  gh.setParamValue("gate", 1);
  delay(5000);
  gh.setParamValue("gate", 0);
  delay(500);
  i++;
  if(i>11){
    i=0;
  }
}
