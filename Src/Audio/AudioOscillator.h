#pragma once

#include "AudioCommon.h"
#include "AudioComponent.h"

// Params:
// 0	waveform (see WaveType enum for values)
//		- sine:        1 full cycle of sine
//		- square:      high for Td, then low for (1-Td)
//		- triangle:    rising from low to high for Tr, then falling from high to low for (1-Tr)
//      - sawtooth:    rising from low to high over 1 period
//		- white noise: random samples distributed uniformly
// 1	wave frequency (in Hz)
// 2	[unimplemented] wave phase offset (in cycles, [-0.5,0.5])
// 3	wave amplitude
// 4	wave center
// 5	waveform specific parameter:
//		- sine:        not used
//		- square:      duty cycle (Td) in cycle percent
//		- triangle:    rise time (Tr) in cycle percent
//		- sawtooth:    not used
//		- white noise: not used
class AudioOscillator : public AudioComponent
{
public:
	EnumBegin(WaveType, SINE_WAVE)
		SINE_WAVE = 0,
		SQUARE_WAVE,
		TRIANGLE_WAVE,
		SAWTOOTH_WAVE,
		WHITE_NOISE,
	EnumEnd(WaveType);

public:
	AudioOscillator();

	float nextSample() override;

private:
	// Current phase in cycle percent.
	float mCurrentPhase;

// 	float mWaveFrequency;
// 	float mWavePhaseOffset;
// 	float mWaveAmplitude;
// 	float mWaveCenter;
// 
// 	// Additional params for wave types:
// 	// Sine:     unused
// 	// Square:   duty-cycle (percentage)
// 	// Triangle: peak-position (as a percentage of the cycle)
// 	float mWaveParam;
};
