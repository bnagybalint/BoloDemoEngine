#pragma once

#include "Assist/Common.h"
#include "Assist/Array.h"

#include "AudioCommon.h"

struct IDirectSoundBuffer8;

class AudioComponent;

class AudioTrack
{
private:
	friend class AudioManager;
	friend class AudioGenerator;
public:
	AudioTrack();
	~AudioTrack();

	// Reposition cursor to start
	void reset() { mCursor = 0; }
	// Set data from sample array.
	// NOTE: Samples array can be NULL, in which case the sample data will be uninitialized.
	void setAudioData(float* samples, unsigned int sampleCount);
	void fillAudioDataFrom(AudioComponent* component, unsigned int sampleCount);

	inline int getNumSamples() const { return mData.size(); }
	inline float* getSamples() { return mData.data(); }

private:
	// Array that stores the raw audio samples
	Array<float> mData;
	// Cursor that moves through the samples
	int mCursor;

	// DirectSound buffer
	IDirectSoundBuffer8* mDsBuffer;

private:
	// DirectSound stuff
	IDirectSoundBuffer8* getDsBuffer() const { return mDsBuffer; }
	void createBuffer();
	void releaseBuffer();

};

