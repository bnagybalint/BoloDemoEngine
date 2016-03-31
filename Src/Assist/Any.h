#pragma once

#include "Assist/Common.h"
#include "Assist/Memory.h"
#include "Assist/Typeid.h"

#include <new>

namespace {
	template <typename T>
	void DefaultConstructFunction(void* dstObject, const void* srcObject)
	{
		const T* src = static_cast<const T*>(srcObject);
		new (dstObject)T(*src);
	}
	template <typename T>
	void DefaultDestroyFunction(void* object)
	{
		T* obj = static_cast<T*>(object);
		obj->~T();
	}
}

class Any
{
private:
	typedef void (*ConstructFunction)(void*, const void*);
	typedef void (*DestroyFunction)(void*);

public:

	// Uninitialized ctor
	Any();
	// Initializer ctor
	template <typename T>
	explicit Any(const T& item);
	// Copy ctor
	Any(const Any& other);
	// Dtor
	~Any();


	// Copy another Any.
	Any& operator = (const Any& other);
	template <typename T>
	// Set object stored in the Any.
	Any& operator = (const T& item);

	// Get object stored in the Any.
	template <typename T>
	T get() const;
	// Set object stored in the Any.
	template <typename T>
	void set(const T& item);

	// Set Any to empty.
	void reset();

private:

	void copy(const Any& other);
	void destroy();

private:

	ubyte* mData;
	int    mDataSize;
	TypeID mType;

	ConstructFunction mConstructFunc;
	DestroyFunction mDestroyFunc;
};

template <typename T>
T any_cast(const Any& any)
{
	return any.get<T>();
}

Any::Any()
	: mData(NULL)
	, mDataSize(0)
	, mType(INVALID_TYPEID)
	, mConstructFunc(NULL)
	, mDestroyFunc(NULL)
{
}

template <typename T>
Any::Any(const T& item)
	: mData(NULL)
	, mDataSize(0)
	, mType(INVALID_TYPEID)
	, mConstructFunc(NULL)
	, mDestroyFunc(NULL)
{
	set(item);
}

Any::Any(const Any& other)
	: mData(NULL)
	, mDataSize(0)
	, mType(INVALID_TYPEID)
	, mConstructFunc(NULL)
	, mDestroyFunc(NULL)
{
	copy(other);
}

Any::~Any()
{
	if (mData)
		destroy();
}

Any& Any::operator = (const Any& other)
{
	copy(other);
	return *this;
}

template <typename T>
Any& Any::operator = (const T& item)
{
	set(item);
	return *this;
}

template <typename T>
T Any::get() const
{
	Assert(mData);
	Assert(mType == GetTypeId<T>());
	return *reinterpret_cast<const T*>(mData);
}

template <typename T>
void Any::set(const T& item)
{
	if (mData)
	{
		// Type can not be changed this manner.
		// Use reset before calling this.
		Assert(mType == GetTypeId<T>());

		// Type does not change, we can simply destroy current object and 
		// create the new one, without additional allocation.
		mDestroyFunc(mData);
		mConstructFunc(mData, &item);
	}
	else
	{
		mDataSize = sizeof(T);
		mData = new ubyte[mDataSize];

		mType = GetTypeId<T>();
		mConstructFunc = &DefaultConstructFunction < T > ;
		mDestroyFunc = &DefaultDestroyFunction < T > ;

		mConstructFunc(mData, &item);
	}
}

void Any::copy(const Any& other)
{
	if (other.mData)
	{
		mDataSize = other.mDataSize;
		mData = new ubyte[mDataSize];

		mType = other.mType;
		mConstructFunc = other.mConstructFunc;
		mDestroyFunc = other.mDestroyFunc;

		mConstructFunc(mData, other.mData);
	}
	else
	{
		reset();
	}
}

void Any::reset()
{
	if (mData)
		destroy();
}

void Any::destroy()
{
	Assert(mData);
	Assert(mDestroyFunc);
	mDestroyFunc(mData);

	delete mData; mData = NULL;
	
	mDataSize = 0;
	mConstructFunc = NULL;
	mDestroyFunc = NULL;
}

