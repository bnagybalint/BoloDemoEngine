#pragma once

#include "Assist/Common.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

class Timer
{
public:

	Timer();
	~Timer();

	void start();
	void stop();

	double getTimeMicroseconds() const;
	double getTimeMilliseconds() const;
	double getTimeSeconds() const;

private:

	LARGE_INTEGER mPcFrequency;
	LARGE_INTEGER mPcValueStart;
	LARGE_INTEGER mPcValueEnd;
	bool          mIsRunning;
};

