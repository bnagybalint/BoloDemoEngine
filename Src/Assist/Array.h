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
	Array(const Array<T>& other);
	~Array();
	
	void append(const T& elem);
	void append(const T* elems, int numElems);

	void clear();
	void resize(int newSize);
	void reserve(int newCapacity);
	
	const T* data() const { return mData; }
	T* data() { return mData; }
	int size() const { return mSize; }
	bool isEmpty() const { return mSize == 0; }
	
	const T& operator[] (int idx) const;
	T& operator[] (int idx);
	
#if BDE_GLOBAL_ENABLE_EDITOR_FUNCTIONALITY
public:
	// Extended functionality
	int  eFind(const T& elem) const;
	bool eContains(const T& elem) const;
	void eSwap(int i, int j);
	void eRemove(int idx);
	void eRemoveUnordered(int idx);
	bool eRemoveItem(const T& elem);
	bool eRemoveItemUnordered(const T& elem);

	// Remove first 'num' items
	void eRemoveHead(int num);
	// Remove last 'num' items
	void eRemoveTail(int num);

	template <class Pred>
	void eQuickSort(const Pred& lessPred);
	void eQuickSort();
private:
	template <class Pred>
	void eQuickSortHelper(int first, int last, const Pred& lessPred);
	template <class Pred>
	int  eQuickSortPivot(int first, int last, const Pred& lessPred);
#endif // BDE_GLOBAL_ENABLE_EDITOR_FUNCTIONALITY

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
Array<T>::Array(const Array<T>& other)
	: mData(NULL)
	, mSize(0)
	, mCapacity(0)
{
	append(other.mData, other.mSize);
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
void Array<T>::clear()
{
	mSize = 0;
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
	Assert(idx < mSize); Assert(0 <= idx);
	return mData[idx];
}

template <class T>
T& Array<T>::operator[] (int idx)
{
	Assert(idx < mSize); Assert(0 <= idx);
	return mData[idx];
}

#if BDE_GLOBAL_ENABLE_EDITOR_FUNCTIONALITY
template <class T>
int Array<T>::eFind(const T& elem) const
{
	for (int i = 0; i < mSize; i++)
		if (mData[i] == elem)
			return i;
	return -1;
}
template <class T>
bool Array<T>::eContains(const T& elem) const
{
	return eFind(elem) > 0;
}
template <class T>
void Array<T>::eSwap(int i, int j)
{
	Assert(i < mSize); Assert(0 <= i);
	Assert(j < mSize); Assert(0 <= j);
	Memory::Swap(mData[i], mData[j]);
}
template <class T>
void Array<T>::eRemove(int idx)
{
	Assert(idx < mSize);  Assert(0 <= idx);
	for (int i = idx; i < mSize - 1; i++)
		mData[i] = mData[i + 1];
	mSize--;
}
template <class T>
void Array<T>::eRemoveUnordered(int idx)
{
	Assert(idx < mSize);  Assert(0 <= idx);
	eSwap(idx, mSize);
	mSize--;
}
template <class T>
bool Array<T>::eRemoveItem(const T& elem)
{
	int idx = eFind(elem);
	if (idx < 0)
		return false;

	eRemove(idx);
	return true;
}
template <class T>
bool Array<T>::eRemoveItemUnordered(const T& elem)
{
	int idx = eFind(elem);
	if (idx < 0)
		return false;

	eRemoveUnordered(idx);
	return true;
}

template <class T>
void Array<T>::eRemoveHead(int num)
{
	Assert(num <= mSize);
	int dstIdx = 0;
	int srcIdx = mSize - num;
	while (srcIdx < mSize)
		mData[dstIdx++] = mData[srcIdx++];

	mSize -= num;
}

template <class T>
void Array<T>::eRemoveTail(int num)
{
	Assert(num <= mSize);
	mSize -= num;
}

template <class T>
template <class Pred>
void Array<T>::eQuickSort(const Pred& lessPred)
{
	eQuickSortHelper(0, mSize - 1, lessPred);
}
template <class T>
void Array<T>::eQuickSort()
{
	struct DefaultLessPred {
		bool operator() (const T& lhs, const T& rhs) const { return lhs < rhs; }
	} lessPred;
	eQuickSort(lessPred);
}

template <class T>
template <class Pred>
void Array<T>::eQuickSortHelper(int first, int last, const Pred& lessPred)
{
	if (first < last)
	{
		int pivotIdx = eQuickSortPivot(first, last, lessPred);
		eQuickSortHelper(first, pivotIdx - 1, lessPred);
		eQuickSortHelper(pivotIdx + 1, last, lessPred);
	}
}
template <class T>
template <class Pred>
int Array<T>::eQuickSortPivot(int first, int last, const Pred& lessPred)
{
	int pivotIdx = first;
	T   pivotElem = mData[pivotIdx];
	for (int i = first + 1; i <= last; i++)
	{
		if (lessPred(mData[i], pivotElem))
		{
			pivotIdx++;
			eSwap(i, pivotIdx);
		}
	}
	eSwap(pivotIdx, first);
	return pivotIdx;
}
#endif // BDE_GLOBAL_ENABLE_EDITOR_FUNCTIONALITY
