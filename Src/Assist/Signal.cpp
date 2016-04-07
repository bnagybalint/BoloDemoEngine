#include "Signal.h"

Signal::Signal()
	: mEventHandle()
{
	mEventHandle = CreateEvent(NULL, TRUE, FALSE, NULL);
	Assert(mEventHandle);
}

Signal::~Signal()
{
	SafeCall(CloseHandle(mEventHandle)); mEventHandle = NULL;
}

void Signal::wait()
{
	DWORD result = WaitForSingleObject(mEventHandle, INFINITE);
	Assert(result == WAIT_OBJECT_0); (void)result;
}

void Signal::send()
{
	SafeCall(SetEvent(mEventHandle));
}
