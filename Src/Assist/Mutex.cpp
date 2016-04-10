#include "Mutex.h"

Mutex::Mutex()
	: mMutexHandle(NULL)
{
	mMutexHandle = CreateMutex(NULL, FALSE, NULL);
	Assert(mMutexHandle);
}

Mutex::~Mutex()
{
	SafeCall(CloseHandle(mMutexHandle)); mMutexHandle = NULL;
}

void Mutex::lock()
{
	DWORD result = WaitForSingleObject(mMutexHandle, INFINITE);
	Assert(result == WAIT_OBJECT_0); (void)result;
}

bool Mutex::tryLock()
{
	DWORD result = WaitForSingleObject(mMutexHandle, 0);
	if (result == WAIT_OBJECT_0)
		return true;
	
	Assert(result == WAIT_TIMEOUT);
	return false;
}

void Mutex::release()
{
	SafeCall(ReleaseMutex(mMutexHandle));
}
