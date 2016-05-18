#pragma once

#include "Assist/Common.h"

#include "Assist/String.h"
#include "Assist/Map.h"
#include "Assist/Mutex.h"

class NameGenerator
{
public:

	DECLARE_SINGLETON_HEADER(NameGenerator);

public:

	String generateName(const String& baseName);

private:

	NameGenerator();
	~NameGenerator();

private:

	Mutex mLock;
	Map<String, int> mNameCounters;
};

