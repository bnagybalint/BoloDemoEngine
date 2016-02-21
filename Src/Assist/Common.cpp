#include "Common.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

void RuntimeAssert(bool cond)
{
	if (!cond)
		DebugBreak();
}

