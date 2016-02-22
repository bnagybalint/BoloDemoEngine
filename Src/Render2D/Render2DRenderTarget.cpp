#include "Render2DRenderTarget.h"

#include "Assist/Vector2.h"

#include "Render2D/Render2DCommon.h"
#include "Render2D/Render2DManager.h"
#include "Render2D/Render2DRenderElement.h"
#include "Render2D/Render2DConverter.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <d2d1.h>
#include <d2d1helper.h>

Render2DRenderTarget::Render2DRenderTarget(HWND parentWindowHandle)
	: mWindowHandle(parentWindowHandle)
	, mRenderTarget(NULL)
	, mBrush(NULL)
	, mRenderElements()
	//, mFillColor(Color::WHITE) // TODO solve static variable init problem without CRT
	//, mLineColor(Color::BLACk)
	, mFillColor(1.0f, 1.0f, 1.0f, 1.0f)
	, mLineColor(0.0f, 0.0f, 0.0f, 1.0f)
{
}

Render2DRenderTarget::~Render2DRenderTarget()
{
	if(mRenderTarget)
		destroyDeviceResources();
}

void Render2DRenderTarget::render()
{
	if (!mRenderTarget)
		createDeviceResources();
	Assert(mRenderTarget);
	mRenderTarget->BeginDraw();
	mRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	mRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

	// TODO
	//sortItems();
	renderItems();

	Assert(mRenderTarget);
	HRESULT hr = mRenderTarget->EndDraw();

	if (hr == D2DERR_RECREATE_TARGET)
	{
		hr = S_OK;
		destroyDeviceResources();
	}
	D2D_SafeCall(hr);
}

void Render2DRenderTarget::createDeviceResources()
{
	RECT rc;
	GetClientRect(mWindowHandle, &rc);

	D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

	// Create render target
	Render2DManager* mgr = Render2DManager::getInstance();
	D2D_SafeCall(mgr->getD2DFactory()->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(mWindowHandle, size), &mRenderTarget));

	// Create brush
	D2D_SafeCall(mRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &mBrush));
}

void Render2DRenderTarget::destroyDeviceResources()
{
	Assert(mRenderTarget);
	mRenderTarget->Release(); mRenderTarget = NULL;
	Assert(mBrush);
	mBrush->Release(); mBrush = NULL;
}

void Render2DRenderTarget::sortItems()
{
	// Lower z-order elements should be rendered first:
	// sort lower z-order elements to the front
	struct SortPred
	{
		bool operator () (Render2DRenderElement* lhs, Render2DRenderElement* rhs) const 
		{
			return lhs->getZOrder() < rhs->getZOrder();
		}
	} sortPred;

	mRenderElements.eQuickSort(sortPred);
}

void Render2DRenderTarget::renderItems()
{
	for (int i = 0; i < mRenderElements.size(); i++)
		mRenderElements[i]->render(this);
}

void Render2DRenderTarget::drawLine(const Vector2& v0, const Vector2& v1, float width)
{
	mBrush->SetColor(Render2DConverter::convertToD2D(mLineColor));
	mRenderTarget->DrawLine(Render2DConverter::convertToD2D(v0), Render2DConverter::convertToD2D(v1), mBrush, width);
}

void Render2DRenderTarget::drawRectangle(const Vector2& v0, const Vector2& v1, float borderWidth)
{
	D2D1_RECT_F rc;
	rc.left   = v0.x;
	rc.top    = v0.y;
	rc.right  = v1.x;
	rc.bottom = v1.y;

	mBrush->SetColor(Render2DConverter::convertToD2D(mFillColor));
	mRenderTarget->FillRectangle(rc, mBrush);
	mBrush->SetColor(Render2DConverter::convertToD2D(mLineColor));
	mRenderTarget->DrawRectangle(rc, mBrush, borderWidth);
}


