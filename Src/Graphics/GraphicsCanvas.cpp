#include "GraphicsCanvas.h"

#include "Graphics/GraphicsConverter.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <d2d1.h>
#include <d2d1helper.h>

#include "Graphics/GraphicsManager.h"
#include "Graphics/GraphicsObject.h"

GraphicsCanvas::GraphicsCanvas(const String& name, HWND parentWindowHandle)
	: mName(name)
	, mWindowHandle(parentWindowHandle)
	, mRenderTarget(NULL)
	, mClearColor(Color::WHITE)
	, mObjectList()
	, mObjectListDirty(false)
{
}

GraphicsCanvas::~GraphicsCanvas()
{
	if (mRenderTarget)
		destroyDeviceResources();
}

void GraphicsCanvas::draw()
{
	if (!mRenderTarget)
		createDeviceResources();

	Assert(mRenderTarget);
	mRenderTarget->BeginDraw();
	mRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	mRenderTarget->Clear(GraphicsConverter::convertToD2D(mClearColor));

	sortObjects();
	drawObjects();

	HRESULT hr = mRenderTarget->EndDraw();

	if (hr == D2DERR_RECREATE_TARGET)
	{
		hr = S_OK;
		destroyDeviceResources();
	}

	SafeCall(hr);
}

void GraphicsCanvas::drawObjects()
{
	if (mObjectListDirty)
	{
		sortObjects();
		mObjectListDirty = false;
	}

	for (int i = 0; i < mObjectList.size(); i++)
	{
		GraphicsObject* obj = mObjectList[i];
		obj->draw();
	}
}

void GraphicsCanvas::sortObjects()
{
	// TODO
}

void GraphicsCanvas::createDeviceResources()
{
	RECT rc;
	GetClientRect(mWindowHandle, &rc);

	D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

	// Create render target
	ID2D1Factory* factory = GraphicsManager::getInstance()->getD2DFactory();
	SafeCall(factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(mWindowHandle, size), &mRenderTarget));
}

void GraphicsCanvas::destroyDeviceResources()
{
	Assert(mRenderTarget);
	mRenderTarget->Release(); mRenderTarget = NULL;
}

GraphicsObject* GraphicsCanvas::createGraphicsObject()
{
	GraphicsObject* go = new GraphicsObject(this);
	mObjectList.append(go);
	mObjectListDirty = true;
	return go;
}

void GraphicsCanvas::destroyGraphicsObject(GraphicsObject* obj)
{
	mObjectList.eRemoveItemUnordered(obj);
	mObjectListDirty = true;
	delete obj; obj = NULL;
}
