#pragma once

#include "Assist/Common.h"

#include "AudioCommon.h"

// Track ::= TrackHeader, [Chunk].
// TrackHeader ::= TrackBPM/8, TrackTPB/8, TrackChunkCount/8.
// Chunk ::= ChunkHeader, (ChunkData | [Chunk]).
// ChunkHeader := (ChunkHeader_Composite | ChunkHeader_Data | ChunkHeader_Ref), ChunkRepeatCount/8.
// ChunkHeader_Composite ::= 0/2, ChunkSubChunkCount/6.
// ChunkHeader_Data ::= 1/2, ChunkDataCount/6.
// ChunkHeader_Ref ::= 2/2, ChunkRefSequenceID/6.
// ChunkData ::= [Sample/32].

class AudioTrackReader {
public:
	void readTrack(ubyte* trackDesc, /*out*/void* trackData);
private:
	inline uint8  readUint8 (/*inout*/ubyte*& ptr) { uint8  val = *((uint8 *)(ptr)); ptr += 1; return val; }
	inline uint32 readUint32(/*inout*/ubyte*& ptr) { uint32 val = *((uint32*)(ptr)); ptr += 4; return val; }

	void readChunk(int samplePerTick, ubyte*& inPtr, /*out*/uint32*& outPtr);
};
