#pragma once

#include "AudioCommon.h"
#include "AudioComponent.h"

// Params:
// 0	Coefficient A0 of the Biquad
// 1	Coefficient A1 of the Biquad
// 2	Coefficient A2 of the Biquad
// 3	Coefficient B1 of the Biquad
// 4	Coefficient B2 of the Biquad
// Note: generate coefficients by calcCoeffs_* methods
class AudioBiquadFilter : public AudioComponent
{
public:
	static void calcCoeffs_LPF(float Fc, float Q, /*out*/float* coeffs); // low-pass filter
	static void calcCoeffs_HPF(float Fc, float Q, /*out*/float* coeffs); // high-pass filter
	static void calcCoeffs_BPF(float Fc, float Q, /*out*/float* coeffs); // band-pass filter

public:
	AudioBiquadFilter();

	float nextSampleImpl() override;

private:
	float mZ1;
	float mZ2;
};

