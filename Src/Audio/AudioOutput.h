#pragma once   

#include "AudioCommon.h"
#include "AudioComponent.h"

class AudioOutput : public AudioComponent
{
public:
	float nextSample() override;
};
