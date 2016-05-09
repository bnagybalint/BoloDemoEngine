#include "NameGenerator.h"

#include "Assist/StringConverter.h"

DEFINE_SINGLETON_IMPL(NameGenerator);

NameGenerator::NameGenerator()
	: mNameCounters()
{
}

NameGenerator::~NameGenerator()
{
}

String NameGenerator::generateName(const String& baseName)
{
	int* counterPtr = mNameCounters.find(baseName);
	int counter = 0;
	if (!counterPtr)
	{
		counter = 1;
		mNameCounters.add(baseName, counter);
	}
	else
	{
		counter = *counterPtr;
		mNameCounters[baseName] = counter + 1;
	}

	return baseName + "." + StringConverter::toString(counter);
}
