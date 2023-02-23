#include "noise_gate.h"
#define MULT_16 32767



AudioNoiseGate::AudioNoiseGate():
AudioStream(1, new audio_block_t*),
threshold = 0

AudioNoiseGate::~AudioNoiseGate(){}

void AudioNoiseGate::setThreshold(float t){
    threshold=t*MULT_16;
}

void AudioNoiseGate::update(void){
    audio_block_t* outBlock;
    audio_block_t* inBlock;
    inBlock= receiveReadOnly(0);
    outBlock = allocate();
    if (outBlock) {
        for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
            val = inBlock->data[i];
            if(val>threshold){
                outBlock->data[i] = val;
            }else{
                outBlock->data[i] = 0;
            }     
        }
        transmit(outBlock, 0);
        if(inBlock) release(inBlock);
        release(outBlock);
    }   
}