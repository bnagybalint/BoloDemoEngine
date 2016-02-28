#pragma once

#include "Assist/Common.h"

#include "Audio/AudioComponent.h"

class AudioComponentInputAdapter : public AudioComponent
{
public:

	AudioComponentInputAdapter();
	~AudioComponentInputAdapter();

	float nextSampleImpl() override;

private:

	AudioComponent* mSource;
	AudioComponent* mDestination;
	int             mParamId;
	float           mLastValue;
};

