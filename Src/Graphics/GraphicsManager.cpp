#include "GraphicsManager.h"

#include "Graphics/GraphicsCanvas.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>

DEFINE_SINGLETON_IMPL(GraphicsManager);

GraphicsManager::GraphicsManager()
	: mFactoryD2D(NULL)
	, mFactoryDWrite(NULL)
	, mCanvases()
{
}

GraphicsManager::~GraphicsManager()
{
	// nop, should be deinitialized by now
	Assert(!mFactoryD2D);
	Assert(!mFactoryDWrite);
}
void GraphicsManager::init()
{
	SafeCall(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mFactoryD2D));
	SafeCall(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&mFactoryDWrite)));
}

void GraphicsManager::shutdown()
{
	Assert(mFactoryD2D);
	mFactoryD2D->Release(); mFactoryD2D = NULL;

	Assert(mFactoryDWrite);
	mFactoryDWrite->Release(); mFactoryDWrite = NULL;
}

void GraphicsManager::renderOneFrame()
{
	// FIXME TODO NASTY
	// should be some foreach but map does not support it yet :D
	mCanvases.get("AudioEditorCanvas")->draw();
}

GraphicsCanvas* GraphicsManager::createCanvas(const String& canvasName, HWND windowHandle)
{
	GraphicsCanvas* canvas = new GraphicsCanvas(canvasName, windowHandle);
	mCanvases.add(canvasName, canvas);
	return canvas;
}

GraphicsCanvas* GraphicsManager::getCanvas(const String& canvasName)
{
	return mCanvases.get(canvasName);
}

void GraphicsManager::destroyCanvas(GraphicsCanvas* canvas)
{
	mCanvases.remove(canvas->getName());
	delete canvas; canvas = NULL;
}
