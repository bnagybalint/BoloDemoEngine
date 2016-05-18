#include "NameGenerator.h"

#include "Assist/StringConverter.h"

DEFINE_SINGLETON_IMPL(NameGenerator);

NameGenerator::NameGenerator()
	: mLock()
	, mNameCounters()
{
}

NameGenerator::~NameGenerator()
{
}

String NameGenerator::generateName(const String& baseName)
{
	mLock.lock();

	int* counterPtr = mNameCounters.find(baseName);
	int counter = 0;
	if (!counterPtr)
	{
		counter = 1;
		mNameCounters.add(baseName, counter);
	}
	else
	{
		counter = ++(*counterPtr);
	}

	mLock.release();

	return baseName + "." + StringConverter::toString(counter);
}
