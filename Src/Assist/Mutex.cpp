#include "Mutex.h"

Mutex::Mutex()
	: mCriticalSection()
{
	InitializeCriticalSectionAndSpinCount(&mCriticalSection, 512);
}

Mutex::~Mutex()
{
	DeleteCriticalSection(&mCriticalSection);
}

void Mutex::lock()
{
	EnterCriticalSection(&mCriticalSection);
}

bool Mutex::tryLock()
{
	return (bool)TryEnterCriticalSection(&mCriticalSection);
}

void Mutex::release()
{
	LeaveCriticalSection(&mCriticalSection);
}
