#pragma once

#include "Assist/Common.h"
#include "Assist/Array.h"

#include "Audio/AudioCommon.h"

class AudioTrack;

class AudioComponent
{
public:

#define AC_SET_PARAM(i, data) for(;;) { mParams[i] = reinterpret_cast<uint32>(data); break; }
#define AC_GET_PARAM(i, T)    *((T*)(&mParams[i]))

	EnumBegin(ComponentControl, GAIN)
		GAIN = 0,
		OFFSET,
		PARAM1,
		PARAM2,
		PARAM3,
		PARAM4,
		PARAM5,
		PARAM6,
		CONTROL_COUNT,
	EnumEnd(ComponentControl);
public:
	// Add input to the component
	inline void addInput(AudioComponent* input) { mInputs.append(input); }
	
	// Control the component. This basically means the change of an operational parameter of the component.
	inline void control(int paramId, uint32 data) { mParams[paramId] = data; }
	// Process inputs and get the data
	// NOTE: Template method pattern
	float nextSample();

private:

	// NOTE: Template method pattern: implementation
	virtual float nextSampleImpl() = 0;

protected:
	// Inputs of the component
	Array<AudioComponent*> mInputs;
	// Controls stored in 4-byte data
	uint32 mParams[ComponentControl::CONTROL_COUNT];
};

// #ifdef BDE_GLOBAL_ENABLE_EDITOR_FUNCTIONALITY
// #include <string>
// class AudioFileOutput : public AudioComponent
// {
// public:
// 	AudioFileOutput(const std::string& filename);
// 	void process(/*out*/AudioTrack* result, int sampleStart, int sampleCount) override;
// private:
// 	std::string mFilename;
// };
// #endif // BDE_GLOBAL_ENABLE_EDITOR_FUNCTIONALITY
// 
// class AudioFilterWaveShaper : public AudioComponent
// {
// public:
// 	void process(/*out*/AudioTrack* result, int sampleStart, int sampleCount) override;
// 
// //private:
// 
// };

