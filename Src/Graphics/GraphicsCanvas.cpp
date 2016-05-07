#include "GraphicsCanvas.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <d2d1.h>
#include <d2d1helper.h>

#include "Graphics/GraphicsManager.h"
#include "Graphics/GraphicsObject.h"
#include "Graphics/GraphicsConverter.h"
#include "Graphics/GraphicsScene.h"

GraphicsCanvas::GraphicsCanvas(const String& name, HWND parentWindowHandle)
	: mName(name)
	, mWindowHandle(parentWindowHandle)
	, mRenderTarget(NULL)
	, mViewportDimensions(Vector2::ZERO)
	, mViewCenter(Vector2::ZERO)
	, mZoomFactor(1.0f)
	//, mClearColor(Color::WHITE)
	, mClearColor(Color(0.0f,1.0f,1.0f)) // TODO
{
}

GraphicsCanvas::~GraphicsCanvas()
{
	if (mRenderTarget)
		destroyDeviceResources();
}

void GraphicsCanvas::setViewTransform(const Vector2& center, float zoomFactor)
{
	mViewCenter = center;
	mZoomFactor = zoomFactor;
	updateRenderTargetTransform();
}

void GraphicsCanvas::setModelTransform(const Vector2& translation, float rotation)
{
	mModelTranslation = translation;
	mModelRotation = rotation;
	updateRenderTargetTransform();
}

void GraphicsCanvas::draw()
{
	if (!mRenderTarget)
		createDeviceResources();

	Assert(mRenderTarget);
	mRenderTarget->BeginDraw();
	mRenderTarget->Clear(GraphicsConverter::convertToD2D(mClearColor));

	updateRenderTargetTransform();

	Assert(mScene);
	mScene->draw(this);

	HRESULT hr = mRenderTarget->EndDraw();

	if (hr == D2DERR_RECREATE_TARGET)
	{
		hr = S_OK;
		destroyDeviceResources();
	}

	SafeCall(hr);
}

void GraphicsCanvas::createDeviceResources()
{
	RECT rc;
	GetClientRect(mWindowHandle, &rc);

	D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);
	mViewportDimensions = Vector2(float(size.width), float(size.height));

	// Create render target
	ID2D1Factory* factory = GraphicsManager::getInstance()->getD2DFactory();
	SafeCall(factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(mWindowHandle, size), &mRenderTarget));

	//mRenderTarget->SetAntialiasMode(D2D1_ANTIALIAS_MODE_FORCE_DWORD);
	mRenderTarget->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE);
}

void GraphicsCanvas::destroyDeviceResources()
{
	Assert(mRenderTarget);
	mRenderTarget->Release(); mRenderTarget = NULL;
}

void GraphicsCanvas::updateRenderTargetTransform()
{
	D2D1_MATRIX_3X2_F mx1 = GraphicsConverter::createTransformD2D(-mViewCenter, 0.0f, mZoomFactor);
	D2D1_MATRIX_3X2_F mx2 = GraphicsConverter::createTransformD2D(mViewportDimensions * 0.5f, 0.0f, 1.0f);
	D2D1_MATRIX_3X2_F t_view = mx1 * mx2;
	D2D1_MATRIX_3X2_F t_model = GraphicsConverter::createTransformD2D(mModelTranslation, Math::Rad2Deg(mModelRotation), 1.0f);

	mRenderTarget->SetTransform(t_view * t_model);
}
