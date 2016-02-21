#include "AudioTrackReader.h"

#include "Assist/Memory.h"

void AudioTrackReader::readTrack(ubyte* trackDesc, /*out*/void* trackData)
{
	uint32* outPtr = (uint32*)trackData;
	ubyte*  inPtr  = (ubyte*)trackDesc;
	int bpm = readUint8(inPtr);
	int tpb = readUint8(inPtr);
	int seqCount = readUint8(inPtr);

	// Performing this integer division yields some error in true BPM.
	// The error of this calculation is shown in the table below, for 
	// different BPM-TPB pairs:
	// 
	//       ________________BPM________________ 
	// _TPB_|___60___|___75___|___90___|___120__|
	//  4   | 0      | 0      | 0      | 9.1e-5 |
	//  8   | 9.0e-5 | 0      | 0      | 9.1e-5 |
	//  16  | 9.0e-5 | 0      | 2.7e-4 | 9.1e-5 |
	//  32  | 9.0e-5 | 4.5e-4 | 8.2e-4 | 9.1e-5 |
	//  64  | 9.0e-5 | 4.5e-4 | 8.2e-4 | 1.5e-3 |
	//  128 | 1.5e-3 | 2.3e-3 | 3.0e-3 | 1.5e-3 |
	// 
	// As it can be seen, the error is mostly negligible, the most 
	// severe setting (bpm: 90, tpb: 128) causes 0.003% error, or less 
	// than a second of error in a 5 minute track. This would be 
	// unacceptable otherwise, but hey, this is Demoscene ;)
	int samplePerTick = AUDIO_SAMPLE_FREQ / (tpb * bpm / 60);

	for (int i = 0; i < seqCount; i++)
		readChunk(samplePerTick, inPtr, outPtr);
}

void AudioTrackReader::readChunk(int samplePerTick, ubyte*& inPtr, /*out*/uint32*& outPtr)
{
	int c1 = readUint8(inPtr);
	int ctype = c1 >> 6;
	int ccnt  = c1 & ((1 << 6) - 1);
	int repeat = readUint8(inPtr);

	uint32* copyStart = outPtr;
	switch (ctype)
	{
	case 0:
		// composite chunk
		for (int j = 0; j < ccnt; j++)
			readChunk(samplePerTick, inPtr, outPtr);
		break;
	case 1:
		// data chunk
		for (int j = 0; j < ccnt; j++)
		{
			uint32 value = readUint32(inPtr);
			for (int k = 0; k < samplePerTick; k++)
				*outPtr++ = value;
		}
		break;
	case 2:
		// TODO implement: chunk reference
		Unimplemented();
		break;
	default:
		Unimplemented();
		break;
	}

	uint32  chunkDataLength = outPtr - copyStart;
	for (int i = 1; i < repeat; i++)
	{
		Memory::Memcopy(outPtr, copyStart, chunkDataLength * sizeof(float));
		outPtr += chunkDataLength;
	}
}
