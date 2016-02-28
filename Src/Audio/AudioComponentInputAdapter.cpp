#include "AudioComponentInputAdapter.h"


AudioComponentInputAdapter::AudioComponentInputAdapter()
{
}

AudioComponentInputAdapter::~AudioComponentInputAdapter()
{
}

float AudioComponentInputAdapter::nextSampleImpl()
{
	Assert(mSource);
	Assert(mDestination);

	float value = mSource->nextSample(); // [-1,1]
	if (value != mLastValue)
	{
		// TODO scale data to [valueMin, valueMax]
		mDestination->control(mParamId, value);
		mLastValue = value;
	}
	return 0.0f;
}
