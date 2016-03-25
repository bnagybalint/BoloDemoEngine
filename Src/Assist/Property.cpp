#include "Property.h"

#include "Assist/PropertyOwner.h"

PropertyBase::PropertyBase(PropertyOwner* owner, const String& name)
	: mOwner(owner)
	, mName(name)
{
	mOwner->addProperty(this);
}

PropertyBase::~PropertyBase()
{
	mOwner->removeProperty(this);

	mOwner = NULL;
	mName = "";
}

bool PropertyBase::is (const PropertyBase& other)
{
	return (mOwner == other.mOwner) && (mName == other.mName);
}
