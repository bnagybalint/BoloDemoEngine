#pragma once

#include "Assist/Common.h"

#include <mutex>

class Mutex
{
public:

	Mutex();
	~Mutex();

	// Acquire lock. Blocks thread until lock is seized.
	void lock();
	// Try to acquire lock. Returns false if it failed.
	bool tryLock();

	void release();

private:

	std::mutex mMutexObject;
};

