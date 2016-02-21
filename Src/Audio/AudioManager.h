#pragma once

#include "AudioCommon.h"

#include <windef.h> 

struct IDirectSound8;
struct IDirectSoundBuffer;

class AudioTrack;

class AudioManager
{
public:

	DECLARE_SINGLETON_HEADER(AudioManager);

public:

	void init(HWND windowHandle);
	void shutdown();

	void prepareTrack(AudioTrack* track);
	void playTrack(AudioTrack* track);
	void stopTrack(AudioTrack* track);

	IDirectSound8* getDsDevice() const { return mDsDevice; }

private:

	AudioManager();
	~AudioManager();

private:
	IDirectSound8* mDsDevice;
	IDirectSoundBuffer* mDsPrimaryBuffer;
	
};

