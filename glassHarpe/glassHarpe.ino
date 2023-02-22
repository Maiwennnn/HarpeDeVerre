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

void setup() {
  AudioMemory(6);
  audioShield.enable();
  audioShield.inputSelect(AUDIO_INPUT_MIC);
  audioShield.micGain(10); // in dB
  audioShield.volume(0.5);
  gh.setParamValue("freq", 300);
  
}

void loop() {
  gh.setParamValue("gate", 1);
  delay(5000);
  gh.setParamValue("gate", 0);
  delay(500);
}
