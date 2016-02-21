#include "AudioConverter.h"


/*static*/ int16 AudioConverter::toSampleInt16(float val)
{
	int32 r = int32(val * float(AUDIO_SAMPLE_MAX_INTVALUE) + 0.5f);
	if (r > AUDIO_SAMPLE_MAX_INTVALUE) return AUDIO_SAMPLE_MAX_INTVALUE;
	if (r < -AUDIO_SAMPLE_MAX_INTVALUE) return -AUDIO_SAMPLE_MAX_INTVALUE;
	return int16(r);
}