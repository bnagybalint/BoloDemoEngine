#pragma once

#include "Assist/Common.h"
#include "Assist/String.h"

class StringConverter
{
public:
	static String toString(uint8  val) { return toString((uint64)val); }
	static String toString(uint16 val) { return toString((uint64)val); }
	static String toString(uint32 val) { return toString((uint64)val); }
	static String toString(uint64 val);

	static String toString(int8  val) { return toString((int64)val); }
	static String toString(int16 val) { return toString((int64)val); }
	static String toString(int32 val) { return toString((int64)val); }
	static String toString(int64 val);

	static String toString(float val);

	static String toStringHex(uint64 val);
};

