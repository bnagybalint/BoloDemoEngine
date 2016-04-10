#include "UIDGenerator.h"

DEFINE_SINGLETON_IMPL(UIDGenerator);

UIDGenerator::UIDGenerator()
	: mLock()
	, mNextUID(1)
{
}

UIDGenerator::~UIDGenerator()
{
}

uint64 UIDGenerator::generate()
{
	mLock.lock();
	uint64 uid = mNextUID++;
	mLock.release();
	return uid;
}
