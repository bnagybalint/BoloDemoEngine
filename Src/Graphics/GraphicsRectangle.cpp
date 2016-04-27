#include "GraphicsRectangle.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <d2d1.h>
#include <d2d1helper.h>

#include "Graphics/GraphicsCanvas.h"
#include "Graphics/GraphicsConverter.h"

GraphicsRectangle::GraphicsRectangle()
	: GraphicsObject()
	, mSize(Vector2::ZERO)
	, mFillColor(Color::WHITE)
	, mBorderColor(Color::BLACK)
	, mBorderWidth(1.0f)
	, mFillBrush(NULL)
	, mBorderBrush(NULL)
{
}

GraphicsRectangle::~GraphicsRectangle()
{
	if (mFillBrush)
	{
		mFillBrush->Release();
		mFillBrush = NULL;
	}

	if (mBorderBrush)
	{
		mBorderBrush->Release();
		mBorderBrush = NULL;
	}
}

void GraphicsRectangle::drawImpl(GraphicsCanvas* target)
{
	D2D_RECT_F fillRect;
	fillRect.left   = 0 - (mSize.x / 2.0f);
	fillRect.top    = 0 - (mSize.y / 2.0f);
	fillRect.right  = 0 + (mSize.x / 2.0f);
	fillRect.bottom = 0 + (mSize.y / 2.0f);

	D2D_RECT_F borderRect = fillRect;

	mFillBrush->SetColor(GraphicsConverter::convertToD2D(mFillColor));
	mBorderBrush->SetColor(GraphicsConverter::convertToD2D(mBorderColor));

	target->getD2DRenderTarget()->FillRectangle(fillRect, mFillBrush);
	target->getD2DRenderTarget()->DrawRectangle(borderRect, mBorderBrush, mBorderWidth, NULL);
}

void GraphicsRectangle::createResourcesImpl(GraphicsCanvas* target)
{
	target->getD2DRenderTarget()->CreateSolidColorBrush(GraphicsConverter::convertToD2D(mFillColor), &mFillBrush);
	target->getD2DRenderTarget()->CreateSolidColorBrush(GraphicsConverter::convertToD2D(mBorderColor), &mBorderBrush);
}

void GraphicsRectangle::destroyResourcesImpl(GraphicsCanvas* /*target*/)
{
	Assert(mFillBrush);
	mFillBrush->Release();
	mFillBrush = NULL;
	Assert(mBorderBrush);
	mBorderBrush->Release();
	mBorderBrush = NULL;
}


