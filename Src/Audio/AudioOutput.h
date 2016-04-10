#pragma once

#include "Assist/Common.h"

#include "Audio/AudioCommon.h"
#include "Audio/AudioComponent.h"

class AudioOutput : public AudioComponent
{
public:
	float nextSampleImpl() override;
};
