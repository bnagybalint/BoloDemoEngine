#include "AudioTrack.h"

#include <mmsystem.h>
#include <dsound.h>

#include "Assist/Memory.h"

#include "Audio/AudioManager.h"
#include "Audio/AudioComponent.h"
#include "Audio/AudioConverter.h"

AudioTrack::AudioTrack()
#if BDE_GLOBAL_ENABLE_NICE_INIT
	: mData()
	, mCursor(0)
	, mDsBuffer(NULL)
#endif
{
	reset();
}

AudioTrack::~AudioTrack()
{
#if BDE_GLOBAL_ENABLE_NICE_DESTROY
	if (mDsBuffer)
		releaseBuffer();
#endif
}

void AudioTrack::setAudioData(float* samples, unsigned int sampleCount)
{
	mData.resize(sampleCount);
	if (samples)
	{
		Memory::Memcopy(mData.data(), samples, sampleCount*sizeof(float));
	}
};

void AudioTrack::fillAudioDataFrom(AudioComponent* component, unsigned int sampleCount)
{
	mData.resize(sampleCount);
	for (unsigned int i = 0; i < sampleCount; i++)
	{
		mData[i] = component->nextSample();
	}
}

void AudioTrack::createBuffer()
{
	int dataSize = mData.size() * AUDIO_SAMPLE_SIZE;

	// Set the wave format of secondary buffer that this wave file will be loaded onto.	
	WAVEFORMATEX waveFormat;
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = AUDIO_SAMPLE_FREQ;
	waveFormat.wBitsPerSample = AUDIO_SAMPLE_BITS;
	waveFormat.nChannels = AUDIO_SAMPLE_CHANNELS;
	waveFormat.nBlockAlign = AUDIO_SAMPLE_BLOCKALIGN;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	// Set the buffer description of the secondary sound buffer that the wave file will be loaded onto.
	DSBUFFERDESC bufferDesc;
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS;
	bufferDesc.dwBufferBytes = dataSize;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = &waveFormat;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	// Create a temporary sound buffer with the specific buffer settings.
	IDirectSound8* dsdev = AudioManager::getInstance()->getDsDevice();
	IDirectSoundBuffer* tempBuffer;
	DS_SafeCall(dsdev->CreateSoundBuffer(&bufferDesc, &tempBuffer, NULL));
	// Test the buffer format against the direct sound 8 interface and create the secondary buffer.
	DS_SafeCall(tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&mDsBuffer));

#if BDE_GLOBAL_ENABLE_NICE_DESTROY
	// Release the temporary buffer.
	tempBuffer->Release(); tempBuffer = NULL;
#endif

	// Lock the secondary buffer to write wave data into it.
	int16* bufferPtr;
	DWORD  bufferSize;
	DS_SafeCall(mDsBuffer->Lock(0, dataSize, (void**)&bufferPtr, (DWORD*)&bufferSize, NULL, NULL, 0));

	Assert(bufferSize >= (DWORD)dataSize);
	int16* bufferWritePtr = bufferPtr;
	for (int i = 0; i < mData.size(); i++)
		*bufferWritePtr++ = AudioConverter::toSampleInt16(mData[i]);

	// Unlock the secondary buffer after the data has been written to it.
	DS_SafeCall(mDsBuffer->Unlock((void*)bufferPtr, bufferSize, NULL, 0));
}

void AudioTrack::releaseBuffer()
{
#if BDE_GLOBAL_ENABLE_NICE_DESTROY
	Assert (mDsBuffer);
	mDsBuffer->Release(); mDsBuffer = NULL;
#endif 
}