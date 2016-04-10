#pragma once

#include "Assist/Common.h"
#include "Assist/Mutex.h"

struct UIDGenerator
{
public:

	DECLARE_SINGLETON_HEADER(UIDGenerator);

public:

	uint64 generate();

private:

	UIDGenerator();
	DISABLE_COPY(UIDGenerator);
	~UIDGenerator();

private:

	Mutex mLock;
	uint64 mNextUID;
};