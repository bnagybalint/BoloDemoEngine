#include "Render2DManager.h"

#include "Render2D/Render2DCommon.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <d2d1.h>
#include <d2d1helper.h>

DEFINE_SINGLETON_IMPL(Render2DManager);

Render2DManager::Render2DManager()
	: mFactory(NULL)
{
}

Render2DManager::~Render2DManager()
{
	// nop, should be deinitialized by now
	Assert(!mFactory);
}
void Render2DManager::init()
{
	D2D_SafeCall(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mFactory));
}

void Render2DManager::shutdown()
{
	Assert(mFactory);
	mFactory->Release(); mFactory = NULL;
}
