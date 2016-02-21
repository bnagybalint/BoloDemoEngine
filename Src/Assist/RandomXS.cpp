#include "RandomXS.h"

namespace
{
	static const uint64 RANDOM_XS_MAX = 0xffffffffffffffff;
}

void RandomXorshift::init(uint32 seed)
{
	Assert(seed);
	mState = uint64(seed);
}

uint64 RandomXorshift::randomUint64()
{
	mState ^= mState >> 12; // a
	mState ^= mState << 25; // b
	mState ^= mState >> 27; // c
	return mState * uint64(2685821657736338717);
}

uint32 RandomXorshift::randomUint32()
{
	return randomUint64() & (~int32(0));
}

float RandomXorshift::randomFloat()
{
	return float(randomUint64()) / float(RANDOM_XS_MAX);
}


