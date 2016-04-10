#include "EventReactor.h"


EventReactor::EventReactor()
	: mEventCallbackList()
{
}

EventReactor::~EventReactor()
{
}

// Note: ownership of callback is transfered to the event mediator.
void EventReactor::registerEvent(CallbackBase* callback)
{
	mEventCallbackList.append(callback);
}

void EventReactor::processEvents()
{
	for (int i = 0; i < mEventCallbackList.size(); i++)
	{
		mEventCallbackList[i]->call();
		delete mEventCallbackList[i]; mEventCallbackList[i] = NULL;
	}
}


