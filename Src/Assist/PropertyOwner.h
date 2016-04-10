#pragma once

#include "Assist/Common.h"
#include "Assist/Map.h"
#include "Assist/Event.h"
#include "Assist/Mutex.h"
#include "Assist/String.h"
#include "Assist/Property.h"
#include "Assist/ObjectUID.h"
#include "Assist/Typeid.h"

class PropertyOwner
{
	friend class PropertyBase;

	DECLARE_TYPE_BASETYPE(PropertyOwner);

public:

	typedef Event<PropertyOwner*, PropertyBase*>::EventHandlerDelegate PropertyListenerDelegate;

public:

	// Event called upon property change of the property owner object
	Event<PropertyOwner*, PropertyBase*> propertyChangedEvent;
	// Event called after creation of the property owner object
	static Event<ObjectUID> objectCreatedEvent;
	// Event called before deletion of the property owner object
	static Event<ObjectUID> objectDestroyingEvent;

public:

	// Method to construct property owners. Must be used to be able to fire object created events.
	template <class PropOwnerType, class... Params>
	static PropOwnerType* create(Params... params);
	// Method to destruct property owners. Must be used to be able to fire object destroying events.
	static void destroy(PropertyOwner* propOwner);

	// Get property owner for exclusive access.
	// NOTE: returns NULL if property owner does not exist (maybe because it has been destroyed)
	static PropertyOwner* lockPropertyOwner(ObjectUID uid);
	// Release property owner.
	static void unlockPropertyOwner(PropertyOwner* propOwner);

private:

	static void onPropertyOwnerCreated(PropertyOwner* propOwner);
	static void onPropertyOwnerDestroying(PropertyOwner* propOwner);

private:

	// Lock protecting access to static members of the class
	static Mutex msPropertyOwnerMapLock;
	// Map that contains all property owners
	static Map<ObjectUID, PropertyOwner*> msPropertyOwnerMap;

public:

	ObjectUID getUID() const { return mObjectUID; }

	const PropertyBase* getProperty(const String& propName) const { return mProperties[propName]; }
	PropertyBase* getProperty(const String& propName) { return mProperties[propName]; }

protected:

	PropertyOwner();
	virtual ~PropertyOwner();

private:

	// Register property 
	void addProperty(PropertyBase* prop);
	void removeProperty(PropertyBase* prop);

private:

	// Lock protecting access to members of the object
	Mutex mObjectLock;
	// Unique ID for the object
	ObjectUID mObjectUID;
	// Registered properties
	ObjectMap<String, PropertyBase*> mProperties;
};

template <class PropOwnerType, class... Params>
/*static*/PropOwnerType* PropertyOwner::create(Params... params)
{
	PropOwnerType* propOwner = new PropOwnerType(params...);
	PropertyOwner::onPropertyOwnerCreated(propOwner);
	return propOwner;
}
