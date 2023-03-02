#include <SerialFlash.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <C:\Program Files (x86)\Arduino\hardware\teensy\avr\libraries\SD\src\SD.h>
#include "glassHarp.h"
//---------------------------------------------------------------------------------------
const int myInput = AUDIO_INPUT_MIC;

//---------------------------------------------------------------------------------------
AudioAnalyzeNoteFrequency notefreq;
AudioMixer4               mixer;
AudioOutputI2S         audioOutput; 
AudioInputI2S          audioInput;
AudioAnalyzePeak       aap1;
glassHarp gh;
float note_prec=10;
float threshold =0.2; 
float prevPeak=0;
boolean clavier=false;
int incomingByte; 
float freq; 
//---------------------------------------------------------------------------------------
AudioConnection patchCord0(audioInput, 0, mixer, 0);
AudioConnection patchCord1(mixer, 0, notefreq, 0);
AudioConnection patchCord4(mixer, 0, aap1, 0);
AudioConnection patchCord2(gh, 0, audioOutput, 0);
AudioConnection patchCord3(gh, 0, audioOutput, 1);
AudioControlSGTL5000 audioShield;
//---------------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  AudioMemory(30);
  audioShield.enable();
  audioShield.inputSelect(myInput);
  audioShield.volume(0.8);
  mixer.gain(0,0.8);
  notefreq.begin(0.1);
  pinMode(A0, INPUT);
  pinMode(15, INPUT);
}

void loop() {
  //Serial.printf("haaaa");
    // read back fundamental frequency
    if (digitalRead(15)==HIGH ){
      //Serial.printf("appuyé\n");
      if (clavier==false){
        audioShield.volume(0.8);
        Serial.write("c");
        patchCord0.disconnect();
        clavier=true;
        delay(500); 
      }else {
        audioShield.volume(0.2);
        patchCord0.connect();
        Serial.write("h");
        clavier=false;
        delay(500); 
      }
    }
    if(clavier){
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
          case '*':
            freq=131;
            break;
              
          case 'q':
            freq=139;
            break;
              
          case 's':
            freq=147;
            break;
              
          case 'd':
            freq=156;
            break;
              
          case 'f':
            freq=165;
            break;
              
          case 'g':
            freq=175;
            break;
              
          case 'h':
            freq=185;
            break;
              
          case 'j':
            freq=196;
            break;
              
          case 'k':
            freq=208;
            break;
              
          case 'l':
            freq=220;
            break;
              
          case 'm':
            freq=233;
            break;
              
          case '!':
            freq=247;
            break;
        }
            
        gh.setParamValue("freq", freq);
        gh.setParamValue("gate", 1);
        delay(600);
        gh.setParamValue("gate", 0);
        delay(100);
      }
    }
    else if (notefreq.available() ) {
      float note = notefreq.read();
      float prob = notefreq.probability();
      if(aap1.available()){
        float peak=aap1.read();
        float ecart = note_prec*0.02973;
        if((note>note_prec+ecart or note<note_prec-ecart)and note>99 and note<1001){
          if(peak>threshold){
            Serial.printf("Note: %3.2f | Probability: %.2f, peak:%.2f\n", note, prob,peak);
            gh.setParamValue("freq", note);
            float v =analogRead(A0)*0.0009775171;
            audioShield.volume(v);
            gh.setParamValue("gate", 1);
            delay(600);
            gh.setParamValue("gate", 0);
            delay(100);
            note_prec=note;
            prevPeak=0.8*peak;
          }
        }else if (peak>=prevPeak and note>99 and note<1001){
            
            Serial.printf("La meme Note: %3.2f | Probability: %.2f, peak:%.2f\n", note, prob,peak);
            gh.setParamValue("freq", note);
            float v =analogRead(A0)*0.0009775171;
            audioShield.volume(v);
            gh.setParamValue("gate", 1);
            delay(600);
            gh.setParamValue("gate", 0);
            delay(100);
            note_prec=note;
            prevPeak=peak;
        }
      }
    }
        
        
      else if(aap1.available()){
        float peak=aap1.read();
        if (notefreq.available()){
          float ecart = note_prec*0.02973;
          float note = notefreq.read();
          float prob = notefreq.probability();
          if((note>note_prec+ecart or note<note_prec-ecart)and note>99 and note<1001){
            if(peak>threshold){
              Serial.printf("Note: %3.2f | Probability: %.2f, peak:%.2f\n", note, prob,peak);
              gh.setParamValue("freq", note);
              float v =analogRead(A0)*0.0009775171;
              audioShield.volume(v);
              gh.setParamValue("gate", 1);
              delay(600);
              gh.setParamValue("gate", 0);
              delay(100);
              note_prec=note;
              prevPeak=peak;
            }
          }else if(peak>=prevPeak and note>99 and note<1001){
            Serial.printf("Note: %3.2f | Probability: %.2f, peak:%.2f\n", note, prob,peak);
            gh.setParamValue("freq", note);
            float v =analogRead(A0)*0.0009775171;
            audioShield.volume(0.9-v*0.4);
            gh.setParamValue("gate", 1);
            delay(600);
            gh.setParamValue("gate", 0);
            delay(100);
            note_prec=note;
            prevPeak=0.9*peak;
        }
      }
    }
      
        
}
