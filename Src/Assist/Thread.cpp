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
	mTaskList.pushBack(task);
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

