#pragma once

#include "Assist/Common.h"
#include "Assist/Array.h"

template <class T>
class List
{
public:
	class ListElement
	{
	private:

		friend class List;

	public:

		void setItem(const T& item) { mData = item; }
		const T& getItem() const { return mData; }
		T& getItem() { return mData; }

		const T& operator * () const { return mData; }
		T& operator * () { return mData; }
		const T* operator -> () const { return &mData; }
		T* operator -> () { return &mData; }

		ListElement* getPrevious() const { return mPrev; }
		ListElement* getNext() const { return mNext; }

	private:

		ListElement() : mData(), mPrev(NULL), mNext(NULL) {}
		ListElement(const T& data) : mData(data), mPrev(NULL), mNext(NULL) {}
		~ListElement() {}

	private:

		T mData;
		ListElement* mPrev;
		ListElement* mNext;
	};

public:

	List();
	List(const List<T>& other);
	~List();

	void pushFront(const T& item);
	void pushBack(const T& item);

	void pushFront(const List<T>& list);
	void pushBack(const List<T>& list);

	void popFront();
	void popBack();

	const ListElement* getFirst() const { Assert(mFirst); return mFirst; }
	ListElement* getFirst() { Assert(mFirst); return mFirst; }

	const ListElement* getLast() const { Assert(mLast); return mLast; }
	ListElement* getLast() { Assert(mLast); return mLast; }

	const T& getFirstItem() const { Assert(mFirst); return mFirst->mData; }
	T& getFirstItem() { Assert(mFirst); return mFirst->mData; }

	const T& getLastItem() const { Assert(mLast); return mLast->mData; }
	T& getLastItem() { Assert(mLast); return mLast->mData; }

	bool isEmpty() const { return mFirst == NULL; }

private:

	ListElement* mFirst;
	ListElement* mLast;
};


template <class T>
List<T>::List()
	: mFirst(NULL)
	, mLast(NULL)
{
}

template <class T>
List<T>::List(const List<T>& other)
	: mFirst(NULL)
	, mLast(NULL)
{
	ListElement* cur = other.getFirst();
	while (cur)
	{
		pushBack(cur->getItem());
		cur = cur->getNext();
	}
}

template <class T>
List<T>::~List()
{
	ListElement* next = mFirst;
	while (next)
	{
		ListElement* cur = next;
		next = next->getNext();
		delete cur;
	}
}

template <class T>
void List<T>::pushFront(const T& item)
{
	ListElement* newElem = new ListElement(item);
	newElem->mNext = mFirst;
	if (mFirst)
		mFirst->mPrev = newElem;
	else
		mLast = newElem;
	mFirst = newElem;
}

template <class T>
void List<T>::pushBack(const T& item)
{
	ListElement* newElem = new ListElement(item);
	newElem->mPrev = mLast;
	if (mLast)
		mLast->mNext = newElem;
	else
		mFirst = newElem;
	mLast = newElem;
}

template <class T>
void List<T>::pushFront(const List<T>& list)
{
	Unimplemented();
}

template <class T>
void List<T>::pushBack(const List<T>& list)
{
	Unimplemented();
}

template <class T>
void List<T>::popFront()
{
	ListElement* frontElem = getFirst();
	mFirst = frontElem->mNext;
	if (mFirst)
		mFirst->mPrev = NULL;
	delete frontElem;
}

template <class T>
void List<T>::popBack()
{
	ListElement* backElem = getLast();
	mLast = backElem->mPrev;
	if (mLast)
		mLast->mNext = NULL;
	delete backElem;
}


