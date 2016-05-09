#pragma once

#include "Assist/Common.h"

#include "Assist/String.h"
#include "Assist/Map.h"

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

	Map<String, int> mNameCounters;
};

