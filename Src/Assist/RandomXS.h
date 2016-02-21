#pragma once

#include "Assist/Common.h"

class RandomXorshift
{
public:
	void init(uint32 seed);
	
	uint64 randomUint64();
	uint32 randomUint32();
	float randomFloat();

private:
	uint64 mState;
};

