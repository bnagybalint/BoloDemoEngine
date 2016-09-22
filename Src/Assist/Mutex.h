#pragma once

#include "Assist/Common.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

class Mutex
{
public:

	Mutex();
	DISABLE_COPY(Mutex);
	~Mutex();

	// Acquire lock. Blocks thread until lock is seized.
	void lock();
	// Try to acquire lock. Returns false if it failed.
	bool tryLock();

	void release();

private:

	CRITICAL_SECTION mCriticalSection;
};

