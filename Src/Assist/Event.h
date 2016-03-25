#pragma once

#include "Assist/Common.h"
#include "Assist/Delegate.h"
#include "Assist/ObjectArray.h"

// TODO make class thread-safe
template <class... EventParams>
class Event
{
public:

	typedef Delegate<void(EventParams...)> EventHandlerDelegate;

public:

	Event();
	~Event();

	void operator += (const EventHandlerDelegate& dlg);
	void operator -= (const EventHandlerDelegate& dlg);

	void fire(EventParams... params);

private:

	ObjectArray<EventHandlerDelegate> mListeners;
};

template <class... EventParams>
Event<EventParams...>::Event() 
	: mListeners()
{}

template <class... EventParams>
Event<EventParams...>::~Event() {}

template <class... EventParams>
void Event<EventParams...>::operator += (const EventHandlerDelegate& dlg)
{
	mListeners.append(dlg);
}

template <class... EventParams>
void Event<EventParams...>::operator -= (const EventHandlerDelegate& dlg)
{
	mListeners.eRemove(dlg);
}

template <class... EventParams>
void Event<EventParams...>::fire (EventParams... params)
{
	// NOTE: not protected from concurrent firing and appending
	for (int i = 0; i < mListeners.size(); i++)
	{
		mListeners[i](params...);
	}
}
