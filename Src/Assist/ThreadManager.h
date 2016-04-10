#pragma once

#include "Assist/Common.h"
#include "Assist/Map.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h> 
#include "String.h"

class Thread;

class ThreadManager
{
	friend class Thread;

public:

	DECLARE_SINGLETON_HEADER(ThreadManager);

public:

	Thread* createThread();
	void destroyThread(Thread* th);

	// Pause execution of the current thread until passed thread finishes
	void join(Thread* th);
	// Pause execution of the current thread until any thread in the list finishes
	void joinAny(const Array<Thread*>& ths);
	// Pause execution of the current thread until every thread in the list finishes
	void joinAll(const Array<Thread*>& ths);

	Thread* getCurrent();

	void sleepCurrentThread(unsigned long timeMs);

private:

	ThreadManager();
	DISABLE_COPY(ThreadManager);
	~ThreadManager();

private:

	void registerRunningThread(Thread* th);
	void unregisterRunningThread(Thread* th);

	void joinAnyOrAll(const Array<Thread*>& ths, bool all);

private:

	//ObjectDictionary<String, Thread*> mThreadList;
	Map<HANDLE, Thread*> mRunningThreadList;
};
