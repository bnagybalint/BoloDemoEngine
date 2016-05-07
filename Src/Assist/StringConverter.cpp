#include "StringConverter.h"

#include <cstdio>

/*static*/ String StringConverter::toString(uint64 val)
{
	char buf[64];
	int len = sprintf_s(buf, 64, "%lu", val);
	Assert(len >= 0);
	return String(buf);
}

/*static*/ String StringConverter::toString(int64 val)
{
	char buf[64];
	int len = sprintf_s(buf, 64, "%ld", val);
	Assert(len >= 0);
	return String(buf);
}

/*static*/ String StringConverter::toString(float val)
{
	char buf[64];
	int len = sprintf_s(buf, 64, "%lf", val);
	Assert(len >= 0);
	return String(buf);
}

/*static*/ String StringConverter::toStringHex(uint64 val)
{
	char buf[64];
	int len = sprintf_s(buf, 64, "0x%016lx", val);
	Assert(len >= 0);
	return String(buf);
}

