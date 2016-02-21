#include "Timer.h"

#include "Assist/Common.h"
#include "Assist/Memory.h"

Timer::Timer()
{
	Memory::Memzero(this, sizeof(Timer));
}

Timer::~Timer()
{
}

void Timer::start()
{
	Assert(!mIsRunning);
	mPcValueEnd.QuadPart = 0;
	QueryPerformanceFrequency(&mPcFrequency);

	mIsRunning = true;
	QueryPerformanceCounter(&mPcValueStart);
}

void Timer::stop()
{
	QueryPerformanceCounter(&mPcValueEnd);
	mIsRunning = false;
}

double Timer::getTimeMicroseconds() const
{
	return getTimeSeconds() * double(1e6);
}

double Timer::getTimeMilliseconds() const
{
	return getTimeSeconds() * double(1e3);
}

double Timer::getTimeSeconds() const
{
	LARGE_INTEGER end = mPcValueEnd;
	if (mIsRunning)
		QueryPerformanceCounter(&end);
	LONGLONG diff = end.QuadPart - mPcValueStart.QuadPart;
	return double(diff) / double(mPcFrequency.QuadPart);
}
