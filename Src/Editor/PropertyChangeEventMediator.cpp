#include "PropertyChangeEventMediator.h"

#include "Assist/PropertyOwner.h"
#include "Assist/Property.h"
#include "Assist/Delegate.h"

#include "Editor/Editor.h"

PropertyChangeEventMediator::PropertyChangeEventMediator(ObjectUID propOwnerUID, const String& propName, const HandlerDelegate& handler)
	: mPropertyOwnerUID(propOwnerUID)
	, mPropertyName(propName)
	, mHandler(handler)
{
	PropertyOwner* propOwner = PropertyOwner::lockPropertyOwner(mPropertyOwnerUID);
	if (propOwner)
	{
		propOwner->propertyChangedEvent += Delegate<void(PropertyOwner*, PropertyBase*)>(this, &PropertyChangeEventMediator::onPropertyChanged);
		PropertyOwner::unlockPropertyOwner(propOwner); propOwner = NULL;
	}
}

PropertyChangeEventMediator::~PropertyChangeEventMediator()
{
	// Note: Not possible to unsubscribe as the object is dead by now.
	//       This is not a problem as events do not check their subscribers upon destruction.

	// NOP
}

void PropertyChangeEventMediator::onPropertyChanged(PropertyOwner* propOwner, PropertyBase* prop)
{
	Assert(propOwner->getUID() == mPropertyOwnerUID);
	Assert(prop->getName() == mPropertyName);
	Editor::getInstance()->requestEventCallback(new Callback<void(ObjectUID, const String&)>(mHandler, mPropertyOwnerUID, mPropertyName));
}
