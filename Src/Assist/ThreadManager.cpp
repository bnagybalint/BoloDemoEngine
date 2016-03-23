#include "ThreadManager.h"

#include "Assist/Thread.h"

// Define singleton parts
DEFINE_SINGLETON_IMPL(ThreadManager);

ThreadManager::ThreadManager()
{
}

ThreadManager::~ThreadManager()
{
}

Thread* ThreadManager::createThread()
{
	return new Thread();
}

void ThreadManager::destroyThread(Thread* th)
{
	Assert(!th->isRunning());
	delete th;
}

Thread* ThreadManager::getCurrent()
{
	HANDLE currentThreadHandle = GetCurrentThread();

	// must be found, otherwise it might be the main thread of the application which is not managed by the thread manager
	return mRunningThreadList.get(currentThreadHandle);
}

void ThreadManager::join(Thread* th)
{
	if (th->isFinished())
		return;

	DWORD result = WaitForSingleObject(th->getHandle(), INFINITE);
	Assert(result == WAIT_OBJECT_0); (void)result;
}

void ThreadManager::joinAny(const Array<Thread*>& ths)
{
	joinAnyOrAll(ths, true);
}

void ThreadManager::joinAll(const Array<Thread*>& ths)
{
	joinAnyOrAll(ths, true);
}

void ThreadManager::joinAnyOrAll(const Array<Thread*>& ths, bool all)
{
	Array<HANDLE> threadHandles;
	for (int i = 0; i < ths.size(); i++)
	{
		if (ths[i]->isFinished())
			continue;
		threadHandles.append(ths[i]->getHandle());
	}
	DWORD result = WaitForMultipleObjects((DWORD)threadHandles.size(), threadHandles.data(), (BOOL)all, INFINITE);
	Assert(result == WAIT_OBJECT_0); (void)result;
}

void ThreadManager::registerRunningThread(Thread* th)
{
	Assert(!mRunningThreadList.contains(th->getHandle()));
	mRunningThreadList.add(th->getHandle(), th);
}

void ThreadManager::unregisterRunningThread(Thread* th)
{
	Assert(mRunningThreadList.contains(th->getHandle()));
	mRunningThreadList.remove(th->getHandle());
}
