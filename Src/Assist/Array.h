#pragma once

#include "Assist/Common.h"
#include "Assist/Memory.h"

// Array class for primitive types (integral types, floats, pointers, raw structs).
// WARNING: DO NOT use this class for complex types, possibly with managed resources.
//          This class does not call contructors and destructors of objects stored inside.
//          Get yourself a more sophisticated container ;)
template<class T>
class Array
{
public:
	Array();
	Array(const T* elems, int numElems);
	~Array();
	
	void append(const T& elem);
	void append(const T* elems, int numElems);

	void resize(int newSize);
	void reserve(int newCapacity);
	
	const T* data() const { return mData; }
	T* data() { return mData; }
	int size() const { return mSize; }
	
	const T& operator[] (int idx) const;
	T& operator[] (int idx);
	
private:
	T* mData;
	int mSize;
	int mCapacity;
};

template <class T>
Array<T>::Array()
	: mData(NULL)
	, mSize(0)
	, mCapacity(0)
{
}

template <class T>
Array<T>::~Array()
{
	delete[] mData; mData = NULL;
}

template <class T>
void Array<T>::append(const T& elem)
{
	reserve(mSize + 1);
	mData[mSize++] = elem;
}

template <class T>
void Array<T>::append(const T* elems, int numElems)
{
	Assert(elems);
	Assert(numElems > 0);

	reserve(mSize + numElems);
	Memory::Memcopy(mData + mSize, elems, numElems*sizeof(T));
	mSize += numElems;
}

template <class T>
void Array<T>::resize(int newSize)
{
	T* newData = new T[newSize];
	if (mData)
	{
		Memory::Memcopy(newData, mData, mSize*sizeof(T));
		delete[] mData;
	}
	mData = newData;
	mCapacity = mSize = newSize;
}

template <class T>
void Array<T>::reserve(int newCapacity)
{
	if (newCapacity > mCapacity)
	{
		int c2 = mCapacity * 2;
		newCapacity = (c2 > newCapacity) ? c2 : newCapacity;
		int s = mSize;
		resize(newCapacity);
		mSize = s;
	}
}

template <class T>
const T& Array<T>::operator[] (int idx) const
{
	Assert(idx < mSize);
	Assert(0 <= idx);
	return mData[idx];
}

template <class T>
T& Array<T>::operator[] (int idx)
{
	Assert(idx < mSize);
	Assert(0 <= idx);
	return mData[idx];
}