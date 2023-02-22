#include "MegunoLink.h"
#include "Filter.h"
#include "MyDsp.h"

#define AUDIO_OUTPUTS 1

MyDsp::MyDsp() : 
AudioStream(AUDIO_OUTPUTS, new audio_block_t*[AUDIO_OUTPUTS]),
ExponentialFilter<long> ADCFilter(80,0)

MyDsp::~MyDsp(){}

void MyDsp::update(void) {
     audio_block_t* inBlock;
     audio_block_t* outBlock;
     inBlock = receiveReadOnly(channel);
     outBlock= allocate();

    if (outBlock) {
    for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
        float currentSample = 0; 
        if(inBlock){
            currentSample = inBlock->data[i]
            ADCFilter.Filter(currentSample)
            outBlock->data[i] = ADCFilter.Current();

        }
    }
    transmit(outBlock, channel);
    if(inBlock[channel]) release(inBlock[channel]);
    release(outBlock[channel]);
}
