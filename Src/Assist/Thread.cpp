#include "Thread.h"

#include "Assist/ThreadManager.h"

Thread::Thread()
	: mLock()
	, mState(ThreadState::NotStarted)
	, mThreadHandle(NULL)
	, mTaskList()
{
}

Thread::~Thread()
{
	Assert(mState == ThreadState::Finished);
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
	Assert(mState != ThreadState::Finished);
	mLock.lock();
	mTaskList.pushBack(task);
	mLock.release();
}

void Thread::start()
{
	Assert(mState == ThreadState::NotStarted);
	mLock.lock();
	mThreadHandle = CreateThread(NULL, 0, Thread::startProxy, this, 0, NULL);
	Assert(mThreadHandle);
	mState = ThreadState::Running;
	ThreadManager::getInstance()->registerRunningThread(this);
	mLock.release();
}

void Thread::run()
{
	for (;;)
	{
		mLock.lock();
		if (mTaskList.isEmpty())
		{
			mLock.release();
			break;
		}
		ThreadTaskDelegate nextTask = mTaskList.getFirstItem();
		mTaskList.popFront();
		mLock.release();

		// execute task
		nextTask();
	}

	mLock.lock();
	ThreadManager::getInstance()->unregisterRunningThread(this);
	mState = ThreadState::Finished;
	mLock.release();
}

