#pragma once

#include "Assist/Common.h"

struct Memory
{
	template<class T>
	static void Swap(T& a, T& b);

	static void Memcopy(void* dst, const void* src, size_t numBytes);
	static void Memset(void* dst, ubyte data, size_t numBytes);
	static void Memzero(void* dst, size_t numBytes);
	static int  Memcompare(const void* ptr1, const void* ptr2, size_t numBytes);
	static void Memfill(void* dst, const void* src, size_t numDstBytes, size_t numSrcBytes);

	static int Strlen(const char* cstr);
	static int Strcompare(const char* s1, const char* s2);
};
template<class T>
/*static*/void Memory::Swap(T& a, T& b)
{
	T t = a;
	a = b;
	b = t;
}
