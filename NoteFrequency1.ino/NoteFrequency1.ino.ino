/*
 C     C#    D     Eb    E     F     F#    G     G#    A     Bb    B
 0 16.35 17.32 18.35 19.45 20.60 21.83 23.12 24.50 25.96 27.50 29.14 30.87
 1 32.70 34.65 36.71 38.89 41.20 43.65 46.25 49.00 51.91 55.00 58.27 61.74
 2 65.41 69.30 73.42 77.78 82.41 87.31 92.50 98.00 103.8 110.0 116.5 123.5
 3 130.8 138.6 146.8 155.6 164.8 174.6 185.0 196.0 207.7 220.0 233.1 246.9
 4 261.6 277.2 293.7 311.1 329.6 349.2 370.0 392.0 415.3 440.0 466.2 493.9
 5 523.3 554.4 587.3 622.3 659.3 698.5 740.0 784.0 830.6 880.0 932.3 987.8
 6 1047  1109  1175  1245  1319  1397  1480  1568  1661  1760  1865  1976
 7 2093  2217  2349  2489  2637  2794  2960  3136  3322  3520  3729  3951
 8 4186  4435  4699  4978  5274  5588  5920  6272  6645  7040  7459  7902*/
 
#include <SerialFlash.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <C:\Program Files (x86)\Arduino\hardware\teensy\avr\libraries\SD\src\SD.h>
#include "glassHarp.h"
#include "MyDsp.h"
#include "AudioAnalyzePeak1.h"
//---------------------------------------------------------------------------------------
const int myInput = AUDIO_INPUT_MIC;

//---------------------------------------------------------------------------------------
AudioAnalyzeNoteFrequency notefreq;
AudioPlayMemory           wav_note;
AudioMixer4               mixer;
AudioMixer4               mixer1;
AudioOutputI2S         audioOutput; 
AudioInputI2S          audioInput;
AudioAnalyzePeak1       aap1;
glassHarp gh;
float note_prec=10;
float threshold =0.2; 
float prevPeak=0;
MyDsp d;
boolean traitement=true;
//---------------------------------------------------------------------------------------
AudioConnection patchCord0(audioInput, 0, mixer, 0);
AudioConnection patchCord7(audioInput, 0, mixer1, 0);
AudioConnection patchCord1(mixer, 0, notefreq, 0);
AudioConnection patchCord4(mixer, 0, aap1, 0);
AudioConnection patchCord5(mixer1, 0, audioOutput, 0);
AudioConnection patchCord6(mixer1, 0, audioOutput, 1);
AudioConnection patchCord2(gh, 0, audioOutput, 0);
AudioConnection patchCord3(gh, 0, audioOutput, 1);
AudioControlSGTL5000 audioShield;
//---------------------------------------------------------------------------------------
//digitalWriteFast(LED_BUILTIN, !digitalReadFast(LED_BUILTIN));
//---------------------------------------------------------------------------------------
void setup() {
    AudioMemory(30);
    audioShield.enable();
    patchCord5.disconnect();
    audioShield.inputSelect(myInput);
    audioShield.volume(0.8);
    mixer.gain(0,0.8);
    mixer1.gain(0,0.2);
    //gh.setParamValue("bowPressure", 0.2); 
    /*
     *  Initialize the yin algorithm's absolute
     *  threshold, this is good number.
     */
    notefreq.begin(0.1);
    pinMode(A0, INPUT);
    pinMode(15, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  //Serial.printf("haaaa");
    // read back fundamental frequency
    if (digitalRead(15)==HIGH ){
      //Serial.printf("appuy??\n");
      if (traitement==false){
        audioShield.volume(0.8);
        patchCord6.disconnect();
        patchCord5.disconnect();
        patchCord2.connect();
        patchCord3.connect();
        traitement=true;
      }else {
        audioShield.volume(0.2);
        patchCord2.disconnect();
        patchCord3.disconnect();
        patchCord5.connect();
        patchCord6.connect();
        traitement=false;
      }
    }
    
    if (notefreq.available() ) {
      float note = notefreq.read();
      float prob = notefreq.probability();
      if(aap1.available()){
        float peak=aap1.read();
        float ecart = note_prec*0.02973;
        if((note>note_prec+ecart or note<note_prec-ecart)and note>99 ){
          if(peak>threshold){
            Serial.printf("Note: %3.2f | Probability: %.2f, peak:%.2f\n", note, prob,peak);
            gh.setParamValue("freq", note);
            float v =analogRead(A0)*0.0009775171;
            audioShield.volume(v*peak);
            gh.setParamValue("gate", 1);
            delay(600);
            gh.setParamValue("gate", 0);
            delay(100);
            note_prec=note;
            prevPeak=0.8*peak;
          }
        }else if (peak>=prevPeak and note>99){
            
            Serial.printf("La meme Note: %3.2f | Probability: %.2f, peak:%.2f\n", note, prob,peak);
            gh.setParamValue("freq", note);
            float v =analogRead(A0)*0.0009775171;
            audioShield.volume(v*peak);
            gh.setParamValue("gate", 1);
            delay(600);
            gh.setParamValue("gate", 0);
            delay(100);
            note_prec=note;
            prevPeak=peak;
        }
      }
    }
        
        
      if(aap1.available()){
        float peak=aap1.read();
        if (notefreq.available()){
          float ecart = note_prec*0.02973;
          float note = notefreq.read();
          float prob = notefreq.probability();
          if((note>note_prec+ecart or note<note_prec-ecart)and note>99){
            if(peak>threshold){
              Serial.printf("Note: %3.2f | Probability: %.2f, peak:%.2f\n", note, prob,peak);
              gh.setParamValue("freq", note);
              float v =analogRead(A0)*0.0009775171;
              audioShield.volume(v*peak);
              gh.setParamValue("gate", 1);
              delay(600);
              gh.setParamValue("gate", 0);
              delay(100);
              note_prec=note;
              prevPeak=peak;
            }
          }else if(peak>=prevPeak and note>99){
            Serial.printf("Note: %3.2f | Probability: %.2f, peak:%.2f\n", note, prob,peak);
            gh.setParamValue("freq", note);
            float v =analogRead(A0)*0.0009775171;
            audioShield.volume(v*peak);
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
//Vol=40
