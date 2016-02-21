#include "AudioComponent.h"

// void AudioFilterWaveShaper::process(/*out*/AudioTrack* result, int sampleStart, int sampleCount)
// {
// 	// ACTUALLY IT IS AN AMPLITUDE MODIFIER, but heck cares
// 
// 	//Assert(mInputs.size() == 1);
// 	AudioTrack* part = new AudioTrack();
// 	part->setAudioData(NULL, result->getNumSamples());
// 	mInputs[0]->process(part, sampleStart, sampleCount);
// 
// 	AudioTrack* partVol = new AudioTrack();
// 	partVol->setAudioData(NULL, result->getNumSamples());
// 	mInputs[1]->process(partVol, sampleStart, sampleCount);
// 
// 	float* dstPtr = result->getSamples() + sampleStart;
// 	float* srcPtr = part->getSamples() + sampleStart;
// 	float* srcVolPtr = partVol->getSamples() + sampleStart;
// 	for (int i = 0; i < sampleCount; i++)
// 	{
// 		*dstPtr++ = (*srcPtr++) * (*srcVolPtr++);
// 	}
// }

// #ifdef BDE_GLOBAL_ENABLE_EDITOR_FUNCTIONALITY
// #include <fstream>
// AudioFileOutput::AudioFileOutput(const std::string& filename) : mFilename(filename) {}
// namespace {
// 	void ___write(unsigned char*& ptr, void* data, int N) { Memory::Memcopy(ptr, data, N); ptr += N; }
// 	template<class T>
// 	void ___write(unsigned char*& ptr, const T& a) { ___write(ptr, (void*)&a, sizeof(T)); }
// 	void ___write(unsigned char*& ptr, const char* t) { ___write(ptr, (void*)t, sizeof(char)*strlen(t)); }
// }
// void AudioFileOutput::process(/*out*/AudioTrack* result, int sampleStart, int sampleCount)
// {
// 	//Assert(mInputs.size() == 1);
// 	AudioTrack* part = new AudioTrack();
// 	part->setAudioData(NULL, result->getNumSamples());
// 	mInputs[0]->process(part, sampleStart, sampleCount);
// 
// 	float* bufferData = part->getSamples();
// 	int bufferLen = part->getNumSamples();
// 
// 	int outputDataSize = bufferLen * sizeof(int16);
// 	int outputFileSize = 0;
// 	outputFileSize += 12; // header
// 	outputFileSize += 24; // format
// 	outputFileSize += 8 + outputDataSize; // data chunk
// 
// 	unsigned char* outputFileData = new unsigned char[outputFileSize];
// 
// 	unsigned char* ptr = outputFileData;
// 
// 	// header chunk
// 	___write(ptr, "RIFF");
// 	___write(ptr, uint32(outputFileSize - 8));
// 	___write(ptr, "WAVE");
// 
// 	// format chunk
// 	___write(ptr, "fmt ");
// 	___write(ptr, int32(16));
// 	___write(ptr, int16(1));
// 	___write(ptr, int16(AUDIO_SAMPLE_CHANNELS));
// 	___write(ptr, int32(AUDIO_SAMPLE_FREQ));
// 	___write(ptr, int32(AUDIO_SAMPLE_FREQ * AUDIO_SAMPLE_CHANNELS * AUDIO_SAMPLE_BITS / 8));
// 	___write(ptr, int16(AUDIO_SAMPLE_CHANNELS * AUDIO_SAMPLE_BITS / 8));
// 	___write(ptr, int16(AUDIO_SAMPLE_BITS));
// 
// 	// data chunk
// 	___write(ptr, "data");
// 	___write(ptr, int32(outputDataSize));
// 
// 	int16* dataPtr = (int16*)ptr;
// 	for (int i = 0; i < bufferLen; i++)
// 		*dataPtr++ = AudioConverter::toSampleInt16(bufferData[i]);
// 
// 	std::fstream file;
// 	file.open(mFilename, std::ios::binary | std::ios::out);
// 
// 	ptr = outputFileData;
// 	for (int i = 0; i < outputFileSize; i++)
// 		file.put(*ptr++);
// 
// 	file.close();
// 
// 	delete[] outputFileData;
// }
// #endif // BDE_GLOBAL_ENABLE_EDITOR_FUNCTIONALITY
