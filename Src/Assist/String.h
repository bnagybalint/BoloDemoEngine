#pragma once

#include "Assist/Common.h"
#include "Assist/Array.h"

// TODO Very basic implementation, c'mon, we can do better.
template <class CharType>
class StringBase : private Array<CharType>
{
private:
	template <class CT>
	friend StringBase<CT> operator + (const CharType*, const StringBase<CT>&);
	template <class CT>
	friend StringBase<CT> operator + (const StringBase<CT>&, const CharType*);

public:
	StringBase();
	StringBase(const CharType* str);
	StringBase(const StringBase<CharType>& other);
	~StringBase();

	StringBase<CharType> operator + (const StringBase<CharType>& other) const;
	StringBase<CharType>& operator += (const StringBase<CharType>& other);

	bool operator == (const StringBase<CharType>& other) const;
	bool operator != (const StringBase<CharType>& other) const;
	bool operator < (const StringBase<CharType>& other) const;
	
	StringBase<CharType>& operator = (const CharType* str);
	StringBase<CharType>& operator = (const StringBase<CharType>& other);

	int length() const;

	CharType* cstr();
	const CharType* cstr() const;
};

typedef StringBase<char> String;

template <class CharType>
StringBase<CharType>::StringBase()
	: Array()
{
	resize(1);
	(*this)[0] = '\0';
}
template <class CharType>
StringBase<CharType>::StringBase(const CharType* str)
	: Array()
{
	operator = (str);
}
template <class CharType>
StringBase<CharType>::StringBase(const StringBase<CharType>& other)
	: Array()
{
	operator = (other);
}
template <class CharType>
StringBase<CharType>::~StringBase()
{
	// nop
}
template <class CharType>
StringBase<CharType> StringBase<CharType>::operator + (const StringBase<CharType>& other) const
{
	String result;
	result.resize(length() + other.length() + 1);
	Memory::Memcopy(result.data(), data(), length() * sizeof(CharType));
	Memory::Memcopy(result.data() + length(), other.data(), (other.length() + 1) * sizeof(CharType));
	return result;
}
template <class CharType>
StringBase<CharType>& StringBase<CharType>::operator += (const StringBase<CharType>& other)
{
	int oldLen = length();
	resize(oldLen + other.length() + 1);
	Memory::Memcopy(data() + oldLen, other.data(), (other.length() + 1) * sizeof(CharType));
	return *this;
}
template <class CharType>
bool StringBase<CharType>::operator == (const StringBase<CharType>& other) const
{
	if (length() != other.length())
		return false;
	return Memory::Memcompare(data(), other.data(), length() * sizeof(CharType)) == 0;
}

template <class CharType>
bool StringBase<CharType>::operator != (const StringBase<CharType>& other) const
{
	if (length() != other.length())
		return true;
	return Memory::Memcompare(data(), other.data(), length() * sizeof(CharType)) != 0;
}

template <class CharType>
bool StringBase<CharType>::operator < (const StringBase<CharType>& other) const
{
	if (length() < other.length())
		return true;
	if (length() > other.length())
		return false;
	return Memory::Memcompare(data(), other.data(), length() * sizeof(CharType)) < 0;
}

template <class CharType>
StringBase<CharType>& StringBase<CharType>::operator = (const CharType* str)
{
	int len = 0;
	while (str[len++] != '\0');
	resize(len);
	Memory::Memcopy(data(), str, (len) * sizeof(CharType));
	return *this;
}
template <class CharType>
StringBase<CharType>& StringBase<CharType>::operator = (const StringBase<CharType>& other)
{
	int len = other.length();
	resize(len + 1);
	Memory::Memcopy(data(), other.data(), (len + 1) * sizeof(CharType));
	return *this;
}
template <class CharType>
int StringBase<CharType>::length() const
{
	return size() - 1;
}
template <class CharType>
CharType* StringBase<CharType>::cstr()
{
	return data();
}
template <class CharType>
const CharType* StringBase<CharType>::cstr() const
{
	return data();
}

template <class CharType>
StringBase<CharType> operator + (const CharType* cstr, const StringBase<CharType>& str)
{
	return StringBase<CharType>(cstr) + str;
}

template <class CharType>
StringBase<CharType> operator + (const StringBase<CharType>& str, const CharType* cstr)
{
	return str + StringBase<CharType>(cstr);
}
