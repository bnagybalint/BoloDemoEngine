#pragma once

#include "Assist/Common.h"

#include "Assist/Delegate.h"
#include "Assist/Mutex.h"
#include "Assist/Array.h"

// Class that behaves similar to the Reactor pattern's Reactor:
// - stores events (i.e. Callback objects which represent full function calls)
// - processing of events can be called at a desirable time.
// Note: in itself, this class in NOT thread-safe
class EventReactor
{
public:
	EventReactor();
	DISABLE_COPY(EventReactor);
	~EventReactor();

	// Note: ownership of callback is transfered to the event mediator.
	void registerEvent(CallbackBase* callback);

	void processEvents();

private:

	Array<CallbackBase*> mEventCallbackList;
};
