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
	return TryEnterCriticalSection(&mCriticalSection) != 0;
}

void Mutex::release()
{
	LeaveCriticalSection(&mCriticalSection);
}
