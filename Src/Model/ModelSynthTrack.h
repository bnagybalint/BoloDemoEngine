#pragma once

#include "Assist/Common.h"

class AudioTrack;

class ModelSynthTrack
{
public:
	ModelSynthTrack();
	~ModelSynthTrack();

private:

	AudioTrack* mAudioTrack;
};

