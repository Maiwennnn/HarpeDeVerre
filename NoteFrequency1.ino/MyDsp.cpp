
#include "MyDsp.h"

#define AUDIO_OUTPUTS 1

MyDsp::MyDsp() : 
AudioStream(AUDIO_OUTPUTS, new audio_block_t*[AUDIO_OUTPUTS])
{}

MyDsp::~MyDsp(){}

void MyDsp::setTreshold(float t){
  threshold=t;
}
  

void MyDsp::update(void) {
     audio_block_t* inBlock;
     audio_block_t* outBlock;
     inBlock = receiveReadOnly(0);
     outBlock= allocate();

    if (outBlock) {
      for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
          int currentSample = 0; 
          if(inBlock){
              currentSample = inBlock->data[i];
//              if (currentSample>threshold){
//                outBlock->data[i] = ADCFilter.Current();
//              }
               //Serial.printf("V:%d\n", currentSample);
          }
    }
    //transmit(outBlock, channel);
    if(inBlock) release(inBlock);
    release(outBlock);
  }
}
