#pragma once

#include "Assist/Common.h"
#include "Assist/String.h"

// This macro is used to initialize a property conveniently.
#define PROPERTY_INIT(Name, Value) Name(this, #Name, Value)

class PropertyOwner;

class PropertyBase
{
public:

	bool operator == (const PropertyBase& other);

	const String& getName() const { return mName; }
	PropertyOwner* getOwner() const { return mOwner; }

protected:

	PropertyBase(PropertyOwner* owner, const String& name);
	virtual ~PropertyBase();

private: // uncopyable
	PropertyBase();
	PropertyBase(const PropertyBase& other);
	PropertyBase& operator = (const PropertyBase& other);

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

	operator const T& () const;

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
		mOwner->propertyChanged.fire(mOwner, this);
	}
	return *this;
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
