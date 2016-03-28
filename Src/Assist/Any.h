#pragma once

#include "Assist/Common.h"
#include "Assist/Memory.h"

class Any
{
public:
	template <typename T>
	explicit Any(const T& item);

	Any(const Any& other);
	~Any();

	Any& operator = (const Any& other);
	template <typename T>
	Any& operator = (const T& item);

	template <typename T>
	T getValue() const;
	template <typename T>
	void setValue(const T& item);

private:
	ubyte* mData;
	int    mDataSize;
	int    mType;
};

template <typename T>
Any::Any(const T& item)
{
	mDataSize = sizeof(item);
	mType = GetTypeId<T>();

	Assert(mDataSize > 0);
	mData = new ubyte[mDataSize];
	Memory::Memcopy(mData, &item, mDataSize);
}

Any::Any(const Any& other)
{
	mDataSize = other.mDataSize;
	mType = other.mType;
	mData = new ubyte[mDataSize];
	Memory::Memcopy(mData, &other.mData, mDataSize);
}

Any::~Any()
{
	delete[] mData; mData = NULL;
	mType = 0;
}

Any& Any::operator = (const Any& other)
{
	mDataSize = other.mDataSize;
	mType = other.mType;
	mData = new ubyte[mDataSize];
	Memory::Memcopy(mData, &other.mData, mDataSize);
	return *this;
}

template <typename T>
Any& Any::operator = (const T& item)
{
	setValue(item);
	return *this;
}

template <typename T>
T Any::getValue() const
{
	Assert(mType == GetTypeId<T>());
	return *static_cast<T*>(mData);
}

template <typename T>
void Any::setValue(const T& item)
{
	Assert(mType == GetTypeId<T>());
	Memory::Memcopy(mData, &item, mDataSize);
}
