#pragma once

#include "Assist/Common.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

// Represent a synchronization signal object.
// When wait is called on a signal instance, the calling thread is blocked until 
class Signal
{
public:

	Signal();
	DISABLE_COPY(Signal);
	~Signal();

	// Blocks thread until a notify is called on the monitor.
	void wait();
	// Awaken every thread waiting on the signal.
	void send();

private:

	HANDLE mEventHandle;
};

