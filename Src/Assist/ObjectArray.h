#pragma once

#include "Assist/Common.h"

// ObjectArray class for complex types (classes with defined copy and default constructor).
// NOTE: Using this class for primitive types generally has a performance impact when 
//       compared to Array<T>. Use of Array<T> is recommended for memory-copyable types.
template<class T>
class ObjectArray
{
public:
	ObjectArray();
	ObjectArray(const T* elems, int numElems);
	~ObjectArray();

	void append(const T& elem);
	void append(const T* elems, int numElems);

	void clear();
	void resize(int newSize);
	void reserve(int newCapacity);

	const T* data() const { return mData; }
	T* data() { return mData; }
	int size() const { return mSize; }

	const T& operator[] (int idx) const;
	T& operator[] (int idx);

#if BDE_GLOBAL_ENABLE_EDITOR_FUNCTIONALITY
public:
	// Extended functionality
	int  eFind(const T& elem) const;
	void eSwap(int i, int j);
	bool eRemove(const T& elem);
	bool eRemoveUnordered(const T& elem);

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
ObjectArray<T>::ObjectArray()
	: mData(NULL)
	, mSize(0)
	, mCapacity(0)
{
}

template <class T>
ObjectArray<T>::~ObjectArray()
{
	delete[] mData; mData = NULL;
}

template <class T>
void ObjectArray<T>::append(const T& elem)
{
	reserve(mSize + 1);
	mData[mSize++] = elem;
}

template <class T>
void ObjectArray<T>::append(const T* elems, int numElems)
{
	Assert(elems);
	Assert(numElems > 0);

	reserve(mSize + numElems);
	for (int i = 0; i < numElems; i++)
		append(elems[i]);
}

template <class T>
void ObjectArray<T>::clear()
{
	mSize = 0;
}

template <class T>
void ObjectArray<T>::resize(int newSize)
{
	T* newData = new T[newSize];
	if (mData)
	{
		for (int i = 0; i < mSize; i++)
			newData[i] = mData[i];
		delete[] mData;
	}
	mData = newData;
	mCapacity = mSize = newSize;
}

template <class T>
void ObjectArray<T>::reserve(int newCapacity)
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
const T& ObjectArray<T>::operator[] (int idx) const
{
	Assert(idx < mSize); Assert(0 <= idx);
	return mData[idx];
}

template <class T>
T& ObjectArray<T>::operator[] (int idx)
{
	Assert(idx < mSize); Assert(0 <= idx);
	return mData[idx];
}

#if BDE_GLOBAL_ENABLE_EDITOR_FUNCTIONALITY
template <class T>
int ObjectArray<T>::eFind(const T& elem) const
{
	for (int i = 0; i < mSize; i++)
		if (mData[i] == elem)
			return i;
	return -1;
}
template <class T>
void ObjectArray<T>::eSwap(int i, int j)
{
	Assert(i < mSize); Assert(0 <= i);
	Assert(j < mSize); Assert(0 <= j);
	Memory::Swap(mData[i], mData[j]);
}
template <class T>
bool ObjectArray<T>::eRemove(const T& elem)
{
	int idx = eFind(elem);
	if (idx < 0)
		return false;

	for (int i = idx; i < mSize - 1; i++)
		mData[i] = mData[i + 1];
	mSize--;

	return true;
}
template <class T>
bool ObjectArray<T>::eRemoveUnordered(const T& elem)
{
	int idx = eFind(elem);
	if (idx < 0)
		return false;

	eSwap(idx, --mSize);
	return true;
}
template <class T>
template <class Pred>
void ObjectArray<T>::eQuickSort(const Pred& lessPred)
{
	eQuickSortHelper(0, mSize - 1, lessPred);
}
template <class T>
void ObjectArray<T>::eQuickSort()
{
	struct DefaultLessPred {
		bool operator() (const T& lhs, const T& rhs) const { return lhs < rhs; }
	} lessPred;
	eQuickSort(lessPred);
}

template <class T>
template <class Pred>
void ObjectArray<T>::eQuickSortHelper(int first, int last, const Pred& lessPred)
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
int ObjectArray<T>::eQuickSortPivot(int first, int last, const Pred& lessPred)
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
