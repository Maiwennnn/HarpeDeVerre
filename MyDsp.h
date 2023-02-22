#ifndef faust_teensy_h_
#define faust_teensy_h_

#include "Arduino.h"
#include "AudioStream.h"
#include "Audio.h"
#include "MegunoLink.h"
#include "Filter.h"


class MyDsp : public AudioStream
{
  public:
    MyDsp();
    ~MyDsp();
    ExponentialFilter<long> ADCFilter;
    
    virtual void update(void);
};

#endif