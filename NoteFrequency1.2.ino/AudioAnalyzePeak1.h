#include "Arduino.h"
#include "AudioStream.h"

class AudioAnalyzePeak1 : public AudioStream
{
public:
	AudioAnalyzePeak1(void) : AudioStream(1, inputQueueArray) {
		min_sample = 32767;
		max_sample = -32768;
	}
	bool available(void) {
		__disable_irq();
		bool flag = new_output;
		if (flag) new_output = false;
		__enable_irq();
		return flag;
	}
	float read(void) {
		__disable_irq();
		int min = min_sample;
		int max = max_sample;
		min_sample = 32767;
		max_sample = -32768;
		__enable_irq();
		min = abs(min);
		max = abs(max);
		if (min > max) max = min;
		return (float)max / 32767.0f;
	}
	float readPeakToPeak(void) {
		__disable_irq();
		int min = min_sample;
		int max = max_sample;
		min_sample = 32767;
		max_sample = -32768;
		__enable_irq();
		return (float)(max - min) / 32767.0f;
	}

	virtual void update(void);
private:
	audio_block_t *inputQueueArray[1];
	volatile bool new_output;
	int16_t min_sample;
	int16_t max_sample;
};
