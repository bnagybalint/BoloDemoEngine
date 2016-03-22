#include "Thread.h"

Thread::Thread()
	: mThreadHandle(NULL)
	, mTaskListMutex()
	, mTaskList()
{
}

Thread::~Thread()
{
	SafeCall(CloseHandle(mThreadHandle)); mThreadHandle = NULL;
}

/*static*/
DWORD WINAPI Thread::startProxy(LPVOID param)
//void Thread::startProxy(Thread* t)
{
	Thread* t = (Thread*)param;
	t->run();
	return 0;
}

void Thread::addTask(const ThreadTaskDelegate& task)
{
	mTaskListMutex.lock();
	mTaskList.pushBack(task);
	mTaskListMutex.release();
}

void Thread::start()
{
	mThreadHandle = CreateThread(NULL, 0, Thread::startProxy, this, 0, NULL);
}

void Thread::join()
{
	// Note: not thread-safe, I know
	Assert(mThreadHandle);
	WaitForSingleObject(mThreadHandle, INFINITE);
}

void Thread::run()
{
	for (;;)
	{
		mTaskListMutex.lock();
		if (mTaskList.isEmpty())
		{
			mTaskListMutex.release();
			break;
		}
		ThreadTaskDelegate nextTask = mTaskList.getFirstItem();
		mTaskList.popFront();
		mTaskListMutex.release();

		// execute task
		nextTask();
	}
}

