#include "Mutex.h"


Mutex::Mutex()
	: mMutexObject()
{
}

Mutex::~Mutex()
{
}

void Mutex::lock()
{
	mMutexObject.lock();
}

bool Mutex::tryLock()
{
	return mMutexObject.try_lock();
}

void Mutex::release()
{
	mMutexObject.unlock();
}
