#pragma once

#include "Assist/Common.h"
#include "Assist/Delegate.h"
#include "Assist/Mutex.h"
#include "Assist/Array.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

class Thread
{
public:
	typedef Delegate<void()> ThreadTaskDelegate;

private:

	static DWORD WINAPI startProxy(LPVOID);
	//static void startProxy(Thread* t);

public:

	Thread();
	~Thread();

	// Append an item at the end of this thread's task list;
	void addTask(const ThreadTaskDelegate& task);

	// Start processing of tasks in the task list
	void start();
	// Current thread waits until this thread has finished.
	// TODO move to a thread manager
	//      - along with creation and destruction of thread
	//      - along with a new function: joinAll()
	void join();

private:

	// Primary loop for this thread that processes tasks one after the other.
	void run();

private:

	HANDLE mThreadHandle;

	Mutex mTaskListMutex;
	Array<ThreadTaskDelegate> mTaskList;

};

