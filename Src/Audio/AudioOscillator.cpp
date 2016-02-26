#include "AudioOscillator.h"

#include "Assist/MathCommon.h"

namespace
{
	const int PARAM_WAVETYPE  = AudioComponent::ComponentControl::PARAM1;
	const int PARAM_FREQ      = AudioComponent::ComponentControl::PARAM2;
	const int PARAM_PHASE     = AudioComponent::ComponentControl::PARAM3;
	const int PARAM_SPEC      = AudioComponent::ComponentControl::PARAM4;
}

AudioOscillator::AudioOscillator()
	: mCurrentPhase(0.0f)
{
}

float AudioOscillator::nextSampleImpl()
{
	static int dbgCtr = 0;

	const float freq  = AC_GET_PARAM(PARAM_FREQ,      float);
// 	const float phase = AC_GET_PARAM(PARAM_PHASE,     float);
	const float spec  = AC_GET_PARAM(PARAM_SPEC,      float);
	
	Assert(mCurrentPhase >= 0.0f);
	Assert(mCurrentPhase <= 1.0f);

	float output = 0.0f;
	switch (AC_GET_PARAM(PARAM_WAVETYPE,int))
	{
	case WaveType::SINE_WAVE:
		output = Math::Sin(Math::B_2PI * mCurrentPhase);
		break;

	case WaveType::SQUARE_WAVE:
		output = (mCurrentPhase <= spec) ? 1.0f : -1.0f;
		break;
	case WaveType::TRIANGLE_WAVE:
		output = (mCurrentPhase <= spec) ? Math::Interpolate(-1.0f, 1.0f, mCurrentPhase / spec) : Math::Interpolate(-1.0f, 1.0f, (mCurrentPhase - spec) / (1.0f - spec));
		break;
	case WaveType::SAWTOOTH_WAVE:
		output = Math::Interpolate(-1.0f, 1.0f, mCurrentPhase);
		break;
	case WaveType::WHITE_NOISE:
		Unimplemented();// TODO
		break;
	default:
		Unimplemented();
		break;
	}

	mCurrentPhase += freq / float(AUDIO_SAMPLE_FREQ);
	if (mCurrentPhase > 1.0f)
		mCurrentPhase -= 1.0f;

	dbgCtr++;

	return output;
}
