#ifndef faust_teensy_h_
#define faust_teensy_h_

#include "Arduino.h"
#include "AudioStream.h"
#include "Audio.h"


class MyDsp : public AudioStream
{
  public:
    MyDsp();
    ~MyDsp();
    float threshold;
    
    virtual void update(void);
    void setTreshold(float t);
};

#endif
