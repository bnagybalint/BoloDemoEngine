#pragma once

#include "Assist/Common.h"

#include "Assist/Delegate.h"
#include "Assist/ObjectUID.h"
#include "Assist/String.h"

class PropertyOwner;
class PropertyBase;

class PropertyChangeEventMediator
{
public:
	
	typedef Delegate<void(ObjectUID, const String&)> HandlerDelegate;

public:

	PropertyChangeEventMediator(ObjectUID propOwnerUID, const String& propName, const HandlerDelegate& handler);
	DISABLE_COPY(PropertyChangeEventMediator);
	~PropertyChangeEventMediator();

	// TODO Check what happens when event occurs multiple times in one time-frame. 
	//      Can it cause any problems? Or should we leave it to the receiver to handle such a case?
	void onPropertyChanged(PropertyOwner* propOwner, PropertyBase* prop);

private:
	
	ObjectUID       mPropertyOwnerUID;
	String          mPropertyName;
	HandlerDelegate mHandler;
};

