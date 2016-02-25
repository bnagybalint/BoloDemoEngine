#pragma once

#include "Assist/Common.h"
#include "Assist/Event.h"

class PropertyBase;

class PropertyOwner
{
private:
	typedef Event<PropertyOwner*, PropertyBase*> PropertyChangeEventType;

public:
	typedef PropertyChangeEventType::EventHandlerDelegate PropertyChangeDelegate;
	PropertyChangeEventType propertyChanged;

public:

	PropertyOwner();
	virtual ~PropertyOwner();
};

