#pragma once

#include "Assist/Common.h"

//#define String bla

template <class CharType>
class String2
{
private:

	friend String2 operator + (const CharType* cstr, const String2& str);
	friend String2 operator + (const String2& str, const CharType* cstr);

public:

	String2();
	String2(const CharType* cstr);
	String2(const String2& other);
	~String2();

	int length() const { return mLength(); }
	CharType* cstr() const { return mData; }

	String2& operator = (const CharType* cstr);
	String2& operator = (const String2& other);

	bool operator == (const CharType* cstr) const;
	bool operator == (const String2& other) const;
	bool operator != (const CharType* cstr) const;
	bool operator != (const String2& other) const;

	String2 operator + (const String2& other) const;

private:

	static const int msStaticStringSize = 16;

private:

	struct StringData
	{
		CharType* data;
		int length;
		//uint64 hash;
		int refCount;

		StringData() : data(NULL), length(0), refCount(0) {}
	};

private:

	void switchToShared();

	void addRef();
	void removeRef();

private:

	CharType* mDataPtr;
	int       mLength;
	int       mMode;
	//uint64    mHash;

	union SData {
		CharType    localStatic[msStaticStringSize]; // mode 0
		CharType*   localDynamic;                    // mode 1
		StringData* shared;                          // mode 2
		SData() : shared(NULL) {}
	} mData;
};

template <class CharType>
String2<CharType>::String2()
	: mDataPtr(NULL)
	, mLength(0)
	, mMode(0)
	, mData()
{
	mData.localStatic[0] = '\0';
	mDataPtr = mData.localStatic;
}

template <class CharType>
String2<CharType>::String2(const CharType* cstr)
	: mDataPtr(NULL)
	, mLength(0)
	, mMode(0)
	, mData()
{
	mLength = Memory::Strlen(cstr);
	if (mLength < msStaticStringSize - 1)
	{
		mDataPtr = mData.localStatic;
		mMode = 0;
	}
	else
	{
		mData.localDynamic = new CharType[mLength + 1];
		mDataPtr = mData.localDynamic;
		mMode = 1;
	}

	Memory::Memcopy(mDataPtr, cstr, (mLength + 1) * sizeof(CharType));
}

template <class CharType>
String2<CharType>::String2(const String2& other)
	: mDataPtr(NULL)
	, mLength(other.mLength)
	, mMode(0)
	, mData()
{
	//mLength = other.mLength // already done
	if (other.mMode == 0)
	{
		mDataPtr = mData.localStatic;
		Memory::Memcopy(mDataPtr, other.mDataPtr, (mLength + 1) * sizeof(CharType));
		mMode = 0;
	}
	else if (other.mMode == 1)
	{
		const_cast<String2&>(other).switchToShared();

		mData.shared = other.mData.shared;
		mDataPtr = mData.shared->data;
		
		addRef();
		mMode = 2;
	}
	else if (other.mMode == 2)
	{
		mData.shared = other.mData.shared;
		mDataPtr = mData.shared->data;
		
		addRef();
	}
	else
	{
		Unimplemented();
	}
}

template <class CharType>
String2<CharType>::~String2()
{
	if (mMode == 0)
	{
		// NOP
	}
	else if (mMode == 1)
	{
		delete[] mData.localDynamic; mData.localDynamic = NULL;
	}
	else if (mMode == 2)
	{
		removeRef();
	}
	else
	{
		Unimplemented();
	}

	mDataPtr = NULL;
	mLength = 0;
}

template <class CharType>
void String2<CharType>::switchToShared()
{
	if (mMode == 0)
	{
		Unsupported();
	}
	if (mMode == 1)
	{
		StringData* sdata = new StringData();

		sdata->length = mLength;
		sdata->refCount = 0;
		sdata->data = new CharType[mLength + 1];
		Memory::Memcopy(sdata->data, mDataPtr, (mLength + 1) * sizeof(CharType));

		mData.shared = sdata;
		mDataPtr = sdata->data;

		addRef();
		mMode = 2;
	}
	else if (mMode == 2)
	{
		Unsupported();
	}
	else
	{
		Unimplemented();
	}
}

template <class CharType>
void String2<CharType>::addRef()
{
	Assert(mData.shared->refCount >= 0);
	++mData.shared->refCount;
}

template <class CharType>
void String2<CharType>::removeRef()
{
	Assert(mData.shared->refCount > 0);
	--mData.shared->refCount;
	if (mData.shared->refCount == 0)
	{
		delete[] mData.shared->data; mData.shared->data = NULL;
		mData.shared->length = 0;
	}
}

template <class CharType>
String2<CharType>& String2<CharType>::operator = (const CharType* cstr)
{
	Unimplemented();
}

template <class CharType>
String2<CharType>& String2<CharType>::operator = (const String2& other)
{
	Unimplemented();
}

template <class CharType>
bool String2<CharType>::operator == (const CharType* cstr) const
{
	return Memory::Strcompare(mDataPtr, other.mDataPtr) == 0;
}

template <class CharType>
bool String2<CharType>::operator == (const String2& other) const
{
	if (other.mMode == 2 && mData.shared == other.mData.shared)
		return true;
	return Memory::Strcompare(mDataPtr, other.mDataPtr) == 0;
}

template <class CharType>
bool String2<CharType>::operator != (const CharType* cstr) const
{
	return Memory::Strcompare(mDataPtr, other.mDataPtr) != 0;
}

template <class CharType>
bool String2<CharType>::operator != (const String2& other) const
{
	if (other.mMode == 2 && mData.shared == other.mData.shared)
		return false;
	return Memory::Strcompare(mDataPtr, other.mDataPtr) != 0;
}


template <class CharType>
String2<CharType> String2<CharType>::operator + (const String2& other) const
{
	String2 res;
	res.mLength = mLength + other.mLength;
	if (res.mLength < msStaticStringSize - 1)
	{
		mDataPtr = mData.localStatic;
		mMode = 0;
	}
	else
	{
		mData.localDynamic = new CharType[mLength + 1];
		mDataPtr = mData.localDynamic;
		mMode = 1;
	}

	Memory::Memcopy(mDataPtr, other.mDataPtr, mLength * sizeof(CharType));
	Memory::Memcopy(mDataPtr + mLength, other.mDataPtr, (other.mLength + 1) * sizeof(CharType)); // incl. termination
}

template <class CharType>
/*friend*/ String2<CharType> operator + (const CharType* cstr, const String2<CharType>& str)
{
	Unimplemented();
}

template <class CharType>
/*friend*/ String2<CharType> operator + (const String2<CharType>& str, const CharType* cstr)
{
	Unimplemented();
}
