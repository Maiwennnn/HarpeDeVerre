#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <C:\Program Files (x86)\Arduino\hardware\teensy\avr\libraries\SD\src\SD.h>
#include <SerialFlash.h>

const int myInput = AUDIO_INPUT_MIC;

AudioAnalyzeNoteFrequency notefreq;
AudioInputI2S          audioInput; 
AudioMixer4               mixer;
AudioConnection patchCord1(audioInput, 0, mixer, 0);
AudioConnection patchCord2(mixer, 0, notefreq, 0);
AudioControlSGTL5000 audioShield;

void setup() {
  // put your setup code here, to run once:
  AudioMemory(12);
  audioShield.enable();
  audioShield.inputSelect(myInput);
  notefreq.begin(0.15);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (notefreq.available()) {
        float note = notefreq.read();
        float prob = notefreq.probability();
        Serial.printf("Note: %3.2f | Probability: %.2f\n", note, prob);
    }

}
