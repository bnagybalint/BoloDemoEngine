#include "AudioAdsrEnvelope.h"

// 0	gate (on/off)
// 1	Ta attack time
// 2	Td decay time
// 3	Vs sustain level
// 4	Tr release time

namespace
{
	const int PARAM_GATE          = 0;
	const int PARAM_ATTACK_RATE   = 1;
	const int PARAM_DECAY_RATE    = 2;
	const int PARAM_SUSTAIN_LEVEL = 3;
	const int PARAM_RELEASE_RATE  = 4;
}

AudioAdsrEnvelope::AudioAdsrEnvelope()
	: mState(AdsrState::SUSTAIN)
	, mLevel(0.0f)
{
}


float AudioAdsrEnvelope::nextSample()
{
	Assert(mInputs.size() == 1);

	if (AC_GET_PARAM(PARAM_GATE, int))
		if (mState == AdsrState::OFF || mState == AdsrState::SUSTAIN)
			mState = AdsrState::ATTACK;
		else;
	else
		mState = AdsrState::RELEASE;

	const float Ta = AC_GET_PARAM(PARAM_ATTACK_RATE, float);
	const float Td = AC_GET_PARAM(PARAM_DECAY_RATE, float);
	const float Vs = AC_GET_PARAM(PARAM_SUSTAIN_LEVEL, float);
	const float Tr = AC_GET_PARAM(PARAM_RELEASE_RATE, float);

	switch (mState)
	{
	case AdsrState::OFF:
		mLevel = 0.0f;
		break;
	case AdsrState::ATTACK:
		mLevel += 1.0f / (Ta* float(AUDIO_SAMPLE_FREQ));
		if (mLevel >= 1.0f)
			mState = AdsrState::DECAY;
		break;

	case AdsrState::DECAY:
		mLevel -= (1.0f - Td) / (Td * float(AUDIO_SAMPLE_FREQ));
		if (mLevel <= Vs)
		{
			mLevel = Vs;
			mState = AdsrState::SUSTAIN;
		}
		break;

	case AdsrState::SUSTAIN:
		// nop
		break;

	case AdsrState::RELEASE:
		mLevel -= 1.0f / (Tr * float(AUDIO_SAMPLE_FREQ));
		if (mLevel <= 0.0f)
			mState = AdsrState::OFF;
		break;

	default:
		Unimplemented();
		break;
	}

	dbglev.append(mLevel);
	dbgsta.append(mState);

	return mLevel * mInputs[0]->nextSample();
}
