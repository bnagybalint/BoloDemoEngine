#pragma once

#include "Assist/Common.h"
#include "Assist/ObjectUID.h"
#include "Assist/Property.h"
#include "Assist/String.h"

#include "Model/Command.h"

template <class T>
class PropertyChangeCommand : public Command
{
public:

	PropertyChangeCommand(ObjectUID uid, const String& propName, const T& value) 
		: mPropertyOwnerUID(uid)
		, mPropertyName(propName)
		, mValue(val) {}
	virtual ~PropertyChangeCommand() {}

private:

	void executeCommand() override;
	//bool cancelCommand() override; // not needed

private:

	ObjectUID mPropertyOwnerUID;
	String    mPropertyName;
	T         mValue;
};

template <class T>
void PropertyChangeCommand<T>::executeCommand()
{
	PropertyOwner* propOwner = PropertyOwner::lockPropertyOwner(mPropertyOwnerUID);
	
	if (!propOwner)
		fail();

	PropertyBase* prop = propOwner->getProperty(mPropertyName);
	Assert(prop->getType() != GetTypeId<T>());
	Property<T>* propt = static_cast<Property<T>*>(prop);

	(*propt) = mValue;

	PropertyOwner::lockPropertyOwner(propOwner); propOwner = NULL;

	finished();
}

