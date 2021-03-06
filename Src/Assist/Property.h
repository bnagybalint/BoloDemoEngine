#pragma once

#include "Assist/Common.h"
#include "Assist/String.h"
#include "Assist/Typeid.h"

// This macro is used to initialize a property conveniently.
#define PROPERTY_INIT(name, value) name(this, #name, value)

class PropertyOwner;

class PropertyBase
{
public:

	bool is (const PropertyBase& other);

	const String& getName() const { return mName; }
	PropertyOwner* getOwner() const { return mOwner; }

	virtual TypeID getType() const = 0 { return INVALID_TYPEID; };

protected:

	PropertyBase(PropertyOwner* owner, const String& name);
	virtual ~PropertyBase();

private: // uncopyable
	PropertyBase();
	DISABLE_COPY(PropertyBase);

protected:

	PropertyOwner* mOwner;
	String         mName;
};

template<class T>
class Property : public PropertyBase
{
public:

	Property(PropertyOwner* owner, const String& name, const T& initVal);
	~Property();

	Property<T>& operator = (const T& newValue);
	bool operator == (const T& value);
	bool operator != (const T& value);

	operator const T& () const;

	TypeID getType() const override { return GetTypeId<T>(); }

	const T& getValue() const;

private:

	T mValue;
};

template<class T>
Property<T>::Property(PropertyOwner* owner, const String& name, const T& initVal)
	: PropertyBase(owner, name)
	, mValue(initVal)
{
}

template<class T>
Property<T>::~Property()
{
	// nop
}

template<class T>
Property<T>& Property<T>::operator = (const T& newValue)
{
	if (mValue != newValue)
	{
		mValue = newValue;
		mOwner->propertyChangedEvent.fire(mOwner, this);
	}
	return *this;
}

template<class T>
bool Property<T>::operator == (const T& value)
{
	return mValue == value;
}

template<class T>
bool Property<T>::operator != (const T& value)
{
	return mValue != value;
}

template<class T>
Property<T>::operator const T& () const
{
	return mValue;
}

template<class T>
const T& Property<T>::getValue() const {
	return mValue;
};

