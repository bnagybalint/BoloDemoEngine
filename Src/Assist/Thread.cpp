#include "Thread.h"

Thread::Thread()
	: mThreadObject()
	, mTaskListMutex()
	, mTaskList()
{
}

Thread::~Thread()
{
}

/*static*/void Thread::startProxy(Thread* t)
{
	t->run();
}

void Thread::addTask(const ThreadTaskDelegate& task)
{
	mTaskListMutex.lock();
	mTaskList.append(task);
	mTaskListMutex.release();
}

void Thread::start()
{
	mThreadObject = std::thread(Thread::startProxy, this);
}

void Thread::join()
{
	mThreadObject.join();
}

void Thread::run()
{
	for (;;)
	{
		mTaskListMutex.lock();
		if (mTaskList.size() <= 0)
		{
			mTaskListMutex.release();
			break;
		}
		ThreadTaskDelegate nextTask = mTaskList[0];
		mTaskList.eRemove(0);
		mTaskListMutex.release();

		nextTask();
	}
}

