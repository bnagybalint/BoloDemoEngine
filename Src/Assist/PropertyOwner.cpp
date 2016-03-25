#include "PropertyOwner.h"

#include "Assist/Property.h"


/*static*/Event<ObjectUID> PropertyOwner::objectCreated;
/*static*/Event<ObjectUID> PropertyOwner::objectDestroying;

/*static*/Mutex PropertyOwner::msPropertyOwnerMapLock;
/*static*/Map<ObjectUID, PropertyOwner*> PropertyOwner::msPropertyOwnerMap;

PropertyOwner::PropertyOwner()
	: mObjectLock()
	, mObjectUID(INVALID_UID)
	, mProperties()
{
	mObjectUID = GenerateObjectUID();
}

PropertyOwner::~PropertyOwner()
{
	// properties of derived classes will be destroyed by now
	Assert(mProperties.isEmpty());

	
	mObjectUID = INVALID_UID;
}

/*static*/void PropertyOwner::destroy(PropertyOwner* propOwner)
{
	PropertyOwner::onPropertyOwnerDestroying(propOwner);

	delete propOwner; propOwner = NULL;
}

/*static*/void PropertyOwner::onPropertyOwnerCreated(PropertyOwner* propOwner)
{
	msPropertyOwnerMapLock.lock();
	msPropertyOwnerMap.add(propOwner->getUID(), propOwner);
	msPropertyOwnerMapLock.release();

	PropertyOwner::objectCreated.fire(propOwner->getUID());
}

/*static*/void PropertyOwner::onPropertyOwnerDestroying(PropertyOwner* propOwner)
{
	PropertyOwner::objectDestroying.fire(propOwner->getUID());

	msPropertyOwnerMapLock.lock();
	msPropertyOwnerMap.remove(propOwner->getUID());
	msPropertyOwnerMapLock.release();
}

/*static*/PropertyOwner* PropertyOwner::lockPropertyOwner(ObjectUID uid)
{
	msPropertyOwnerMapLock.lock();
	PropertyOwner* propOwner = msPropertyOwnerMap[uid];
	propOwner->mObjectLock.lock();
	msPropertyOwnerMapLock.release();

	return propOwner;
}

/*static*/void PropertyOwner::unlockPropertyOwner(PropertyOwner* propOwner)
{
	msPropertyOwnerMapLock.lock();
	propOwner->mObjectLock.release();
	msPropertyOwnerMapLock.release();
}

void PropertyOwner::addProperty(PropertyBase* prop)
{
	mProperties.add(prop->getName(), prop);
}

void PropertyOwner::removeProperty(PropertyBase* prop)
{
	mProperties.remove(prop->getName());
}


