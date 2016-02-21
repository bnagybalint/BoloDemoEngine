#pragma once

#include "Assist/Array.h"

#include "Audio/AudioComponent.h"

// Params:
// 0	gate (on/off)
// 1	Ta attack time
// 2	Td decay time
// 3	Vs sustain level
// 4	Tr release time
// Note: generate coefficients by calcCoeffs_* methods
class AudioAdsrEnvelope : public AudioComponent
{
public:
	EnumBegin(AdsrState, OFF)
		OFF,
		ATTACK,
		DECAY,
		SUSTAIN,
		RELEASE,
	EnumEnd(AdsrState);

public:
	AudioAdsrEnvelope();

	float nextSample() override;

private:
	AdsrState mState;
	float mLevel;

	Array<float> dbglev;
	Array<int> dbgsta;
};

