#include "AudioManager.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h> 
#include <mmsystem.h>
#include <dsound.h>

#include "AudioTrack.h"

// Define singleton parts
DEFINE_SINGLETON_IMPL(AudioManager);

AudioManager::AudioManager()
#if BDE_GLOBAL_ENABLE_NICE_INIT
	: mDsDevice(NULL)
	, mDsPrimaryBuffer(NULL)
#endif
{
}

AudioManager::~AudioManager()
{
#if BDE_GLOBAL_ENABLE_NICE_DESTROY
	Assert(mDsDevice == NULL);
	Assert(mDsPrimaryBuffer == NULL);
#endif
}

void AudioManager::init(HWND windowHandle)
{
	DSBUFFERDESC bufferDesc;
	WAVEFORMATEX waveFormat;

	// Initialize the direct sound interface pointer for the default sound device.
	DS_SafeCall(DirectSoundCreate8(NULL, &mDsDevice, NULL));

	// Set the cooperative level to priority so the format of the primary sound buffer can be modified.
	DS_SafeCall(mDsDevice->SetCooperativeLevel(windowHandle, DSSCL_PRIORITY));
	
	// Setup the primary buffer description.
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = 0;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = NULL;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	// Get control of the primary sound buffer on the default sound device.
	DS_SafeCall(mDsDevice->CreateSoundBuffer(&bufferDesc, &mDsPrimaryBuffer, NULL));

	// Setup the format of the primary sound bufffer.
	// In this case it is a .WAV file recorded at 44,100 samples per second in 16-bit stereo (cd audio format).
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = AUDIO_SAMPLE_FREQ;
	waveFormat.wBitsPerSample = AUDIO_SAMPLE_BITS;
	waveFormat.nChannels = AUDIO_SAMPLE_CHANNELS;
	waveFormat.nBlockAlign = AUDIO_SAMPLE_BLOCKALIGN;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	// Set the primary buffer to be the wave format specified.
	DS_SafeCall(mDsPrimaryBuffer->SetFormat(&waveFormat));
}

void AudioManager::shutdown()
{
#if BDE_GLOBAL_ENABLE_NICE_DESTROY
	Assert(mDsPrimaryBuffer);
	mDsPrimaryBuffer->Release(); mDsPrimaryBuffer = NULL;
	Assert(mDsDevice);
	mDsDevice->Release(); mDsDevice = NULL;
#endif
}

void AudioManager::prepareTrack(AudioTrack* track)
{
	if (track->getDsBuffer())
		track->releaseBuffer();
	track->createBuffer();
}

void AudioManager::playTrack(AudioTrack* track)
{
	Assert(track->getDsBuffer());
	track->getDsBuffer()->Play(0, 0, DSBPLAY_LOOPING);
}

void AudioManager::stopTrack(AudioTrack* track)
{
	Assert(track->getDsBuffer());
	track->getDsBuffer()->Stop();
}