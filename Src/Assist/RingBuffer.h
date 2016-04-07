#pragma once

#include "Assist/Common.h"

#include "Assist/Memory.h"

// Ring buffer class for primitive types (integral types, floats, pointers, raw structs).
// Represents an efficient, fixed size FIFO-operation container.
// WARNING: DO NOT use this class for complex types, possibly with managed resources.
//          This class does not call contructors and destructors of objects stored inside.
//          Get yourself a more sophisticated container ;)
template <typename T>
class RingBuffer
{
public:

	explicit RingBuffer(unsigned int capacity);
	RingBuffer(const RingBuffer& other);
	~RingBuffer();

	void push(const T& item);
	void pop();

	T& readItem() { Assert(size() > 0); return mData[mReadIndex]; }
	const T& readItem() const { Assert(size() > 0); return mData[mReadIndex]; }

	// Number of items stored in the container
	unsigned int size() const { return mSize; }

	bool isEmpty() const { return mSize == 0; }

private:

	T*           mData;
	unsigned int mSize;       // number of items stored
	unsigned int mCapacity;   // maximum number of items stored
	unsigned int mReadIndex;  // next to be read
	unsigned int mWriteIndex; // next to be written
};

template<typename T>
RingBuffer<T>::RingBuffer(unsigned int capacity)
	: mData(NULL)
	, mSize(0)
	, mCapacity(DefaultCapacity)
	, mReadIndex(0)
	, mWriteIndex(0)
{
	mData = new T[mCapacity];
}

template<typename T>
RingBuffer<T>::RingBuffer(const RingBuffer& other)
	: mData(NULL)
	, mSize(other.mSize)
	, mCapacity(other.mCapacity)
	, mReadIndex(other.mReadIndex)
	, mWriteIndex(other.mWriteIndex)
{
	mData = new T[mCapacity];
	Memory::Memcopy(mData, other.mData, mCapacity*sizeof(T));
}

template<typename T>
RingBuffer<T>::~RingBuffer()
{
	Assert(mData);
	delete[] mData; mData = NULL;
}

template<typename T>
void RingBuffer<T>::push(const T& item)
{
	Assert(size() < mCapacity);
	mData[mWriteIndex++] = item;
	mSize++;
}

template<typename T>
void RingBuffer<T>::pop()
{
	Assert(size() >= 0);
	mReadIndex++;
	mSize--;
}
