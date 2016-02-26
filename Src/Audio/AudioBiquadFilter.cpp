#include "AudioBiquadFilter.h"

#include "Assist/MathCommon.h"

namespace
{
	const int PARAM_A0 = AudioComponent::ComponentControl::PARAM1;
	const int PARAM_A1 = AudioComponent::ComponentControl::PARAM2;
	const int PARAM_A2 = AudioComponent::ComponentControl::PARAM3;
	const int PARAM_B1 = AudioComponent::ComponentControl::PARAM4;
	const int PARAM_B2 = AudioComponent::ComponentControl::PARAM5;
}

// From :http://www.earlevel.com/main/2012/11/26/biquad-c-source-code/
/*static*/ void AudioBiquadFilter::calcCoeffs_LPF(float Fc, float Q, /*out*/float* coeffs)
{
	float freq = Fc / float(AUDIO_SAMPLE_FREQ);
	float K = Math::Tan(Math::B_PI * freq);
	float norm = 1.0f / (1.0f + K/Q + K*K);
	coeffs[PARAM_A0] = K * K * norm;
	coeffs[PARAM_A1] = 2.0f * coeffs[PARAM_A0];
	coeffs[PARAM_A2] = coeffs[PARAM_A0];
	coeffs[PARAM_B1] = 2.0f * (K * K - 1.0f) * norm;
	coeffs[PARAM_B2] = (1.0f - K / Q + K * K) * norm;
}
/*static*/ void AudioBiquadFilter::calcCoeffs_HPF(float Fc, float Q, /*out*/float* coeffs)
{
	float freq = Fc / float(AUDIO_SAMPLE_FREQ);
	float K = Math::Tan(Math::B_PI * freq);
	float norm = 1.0f / (1.0f + K / Q + K*K);
	coeffs[PARAM_A0] = norm;
	coeffs[PARAM_A1] = -2.0f * coeffs[PARAM_A0];
	coeffs[PARAM_A2] = coeffs[PARAM_A0];
	coeffs[PARAM_B1] = 2.0f * (K * K - 1.0f) * norm;
	coeffs[PARAM_B2] = (1.0f - K / Q + K * K) * norm;
}
/*static*/ void AudioBiquadFilter::calcCoeffs_BPF(float Fc, float Q, /*out*/float* coeffs)
{
	float freq = Fc / float(AUDIO_SAMPLE_FREQ);
	float K = Math::Tan(Math::B_PI * freq);
	float norm = 1.0f / (1.0f + K / Q + K*K);
	coeffs[PARAM_A0] = K / Q * norm;
	coeffs[PARAM_A1] = 0.0f;
	coeffs[PARAM_A2] = -coeffs[PARAM_A0];
	coeffs[PARAM_B1] = 2.0f * (K * K - 1.0f) * norm;
	coeffs[PARAM_B2] = (1.0f - K / Q + K * K) * norm;
}

AudioBiquadFilter::AudioBiquadFilter()
	: mZ1(0.0f)
	, mZ2(0.0f)
{
}

float AudioBiquadFilter::nextSampleImpl()
{
	Assert(mInputs.size() == 1);
	float input = mInputs[0]->nextSample();
	float output = input * AC_GET_PARAM(PARAM_A0, float) + mZ1;
	mZ1 = AC_GET_PARAM(PARAM_A1, float) * input - AC_GET_PARAM(PARAM_B1, float) * output + mZ2;
	mZ2 = AC_GET_PARAM(PARAM_A2, float) * input - AC_GET_PARAM(PARAM_B2, float) * output;
	return output;
}
