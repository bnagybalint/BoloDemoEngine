#include "Memory.h"

/*static*/void Memory::Memcopy(void* dst, const void* src, size_t numBytes)
{
	ubyte* d = (ubyte*)dst;
	const ubyte* s = (const ubyte*)src;
	while (numBytes--)
		*d++ = *s++;
}
/*static*/void Memory::Memset(void* dst, ubyte data, size_t numBytes)
{
	ubyte* d = (ubyte*)dst;
	while (numBytes--)
		*d++ = data;
}
/*static*/void Memory::Memzero(void* dst, size_t numBytes)
{
	Memory::Memset(dst, 0x00, numBytes);
}

/*static*/ int Memory::Memcompare(const void* ptr1, const void* ptr2, size_t numBytes)
{
	const ubyte* p1 = (const ubyte*)ptr1;
	const ubyte* p2 = (const ubyte*)ptr2;
	while (numBytes--)
	{
		ubyte b1 = *p1++;
		ubyte b2 = *p2++;
		if (b1 < b2) return 1;
		if (b1 > b2) return -1;
	}
	return 0;
}

/*static*/ void Memory::Memfill(void* dst, const void* src, size_t numDstBytes, size_t numSrcBytes)
{
	ubyte* p = (ubyte*)dst;
	while (numDstBytes)
	{
		Memory::Memcopy(p, src, numSrcBytes > numDstBytes ? numDstBytes : numSrcBytes);
		numDstBytes -= numSrcBytes;
		p += numSrcBytes;
	}
}
