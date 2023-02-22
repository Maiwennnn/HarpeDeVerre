#include <Audio.h>
#include "MyDsp.h"

MyDsp myDsp;
AudioInputI2S in;
AudioOutputI2S out;
AudioControlSGTL5000 audioShield;
AudioConnection patchCord0(in,0,myDsp.lectureFreq,0);
AudioConnection patchCord1(in,1,myDsp.lectureFreq,1);
AudioConnection patchCord2(myDsp,0,out,0);
AudioConnection patchCord3(myDsp,1,out,1);

void setup() {
  AudioMemory(6);
  audioShield.enable();
  audioShield.inputSelect(AUDIO_INPUT_MIC);
  audioShield.micGain(10); // in dB
  audioShield.volume(0.8);
  myDsp.lectureFreq.begin(1);
}

void loop() {
  delay(100);
}
