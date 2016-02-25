#include "Property.h"

#include "Assist/PropertyOwner.h"

PropertyBase::PropertyBase(PropertyOwner* owner, const String& name)
	: mOwner(owner)
	, mName(name)
{
}

PropertyBase::~PropertyBase()
{
	mOwner = NULL;
	mName = "";
}

bool PropertyBase::operator == (const PropertyBase& other)
{
	return (mOwner == other.mOwner) && (mName == other.mName);
}
