#pragma once

#include "Assist/Common.h"
#include "Assist/Delegate.h"
#include "Assist/Mutex.h"
#include "Assist/Array.h"

#include <thread>

class Thread
{
public:
	typedef Delegate<void()> ThreadTaskDelegate;

private:

	static void startProxy(Thread* t);

public:

	Thread();
	~Thread();

	// Append an item at the end of this thread's task list;
	void addTask(const ThreadTaskDelegate& task);

	// Start processing of tasks in the task list
	void start();
	// Current thread waits until this thread has finished.
	void join();

private:

	// Primary loop for this thread that processes tasks one after the other.
	void run();

private:

	std::thread mThreadObject;

	Mutex mTaskListMutex;
	Array<ThreadTaskDelegate> mTaskList;

};

