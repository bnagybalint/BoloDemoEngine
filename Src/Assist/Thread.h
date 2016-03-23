#pragma once

#include "Assist/Common.h"
#include "Assist/Delegate.h"
#include "Assist/Mutex.h"
#include "Assist/List.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

class Thread
{
	friend class ThreadManager;

public:

	typedef Delegate<void()> ThreadTaskDelegate;

public:

	EnumBegin(ThreadState, NotStarted)
		NotStarted,
		Running,
		Finished,
	EnumEnd(ThreadState)

private:

	static DWORD WINAPI startProxy(LPVOID);
	//static void startProxy(Thread* t);

public:

	// Append an item at the end of this thread's task list;
	void addTask(const ThreadTaskDelegate& task);

	// Start processing of tasks in the task list
	void start();

	// TODO these are not thread safe:
	bool isRunning() const { return mState == ThreadState::Running; }
	bool isFinished() const { return mState == ThreadState::Finished; }
	HANDLE getHandle() const { return mThreadHandle; }

private:

	Thread();
	~Thread();

	// Primary loop for this thread that processes tasks one after the other.
	void run();

private:

	Mutex mLock;
	ThreadState mState;
	HANDLE mThreadHandle;
	List<ThreadTaskDelegate> mTaskList;
};

