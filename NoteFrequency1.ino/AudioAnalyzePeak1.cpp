#include <Arduino.h>
#include "AudioAnalyzePeak1.h"

void AudioAnalyzePeak1::update(void)
{
	audio_block_t *block;
	const int16_t *p, *end;
	int32_t min, max;

	block = receiveReadOnly();
	if (!block) {
		return;
	}
	p = block->data;
	end = p + AUDIO_BLOCK_SAMPLES;
	min = min_sample;
	max = max_sample;
	do {
		int16_t d=*p++;
		if (d<min) min=d;
		if (d>max) max=d;
	} while (p < end);
	min_sample = min;
	max_sample = max;
	new_output = true;
	release(block);
}
