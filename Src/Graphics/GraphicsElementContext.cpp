#include "GraphicsElementContext.h"

#include "Graphics/GraphicsConverter.h"
#include "Graphics/GraphicsCanvas.h" 
#include "Graphics/GraphicsManager.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>


GraphicsElementContext::GraphicsElementContext(GraphicsCanvas* parentCanvas)
	: mParentCanvas(parentCanvas)
	, mLineColor(Color::BLACK)
	, mLineWidth(1.0f)
	, mFillColor(Color::WHITE)
	, mFontFamily("Arial")
	, mFontSize(12.0f)
	, mTextAlignment(TextAlignment::Left)
{
	createLineBrush();
	createFillBrush();
	createTextFormat();
}

GraphicsElementContext::~GraphicsElementContext()
{
	if (mLineBrush) destroyLineBrush();
	if (mFillBrush) destroyFillBrush();
	if (mTextFormat) destroyTextFormat();
}

void GraphicsElementContext::setLineColor(const Color& c)
{
	mLineColor = c;
	getLineBrush()->SetColor(GraphicsConverter::convertToD2D(mLineColor));
}
void GraphicsElementContext::setLineWidth(float w)
{
	mLineWidth = w;
}
void GraphicsElementContext::setFillColor(const Color& c)
{
	mFillColor = c;
	getFillBrush()->SetColor(GraphicsConverter::convertToD2D(mFillColor));
}
void GraphicsElementContext::setFontFamily(const String& name)
{
	mFontFamily = name;
	destroyTextFormat();
}
void GraphicsElementContext::setFontSize(float size)
{
	mFontSize = size;
	destroyTextFormat();
}
void GraphicsElementContext::setTextAlignment(const TextAlignment& align)
{
	mTextAlignment = align;
	switch (mTextAlignment)
	{
	case TextAlignment::Left: getTextFormat()->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING); break;
	case TextAlignment::Center: getTextFormat()->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER); break;
	case TextAlignment::Right: getTextFormat()->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING); break;
	case TextAlignment::Justified: getTextFormat()->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_JUSTIFIED); break;
	default: Unimplemented();
	}
}

ID2D1SolidColorBrush* GraphicsElementContext::getLineBrush()
{
	if (!mLineBrush) createLineBrush();
	return mLineBrush;
};

ID2D1SolidColorBrush* GraphicsElementContext::getFillBrush()
{
	if (!mFillBrush) createFillBrush();
	return mFillBrush;
};

IDWriteTextFormat* GraphicsElementContext::getTextFormat()
{
	if (!mTextFormat) createTextFormat();
	return mTextFormat;
};

void GraphicsElementContext::createLineBrush()
{
	Assert(!mLineBrush);
	SafeCall(mParentCanvas->getD2DRenderTarget()->CreateSolidColorBrush(GraphicsConverter::convertToD2D(mLineColor), &mLineBrush));
}
void GraphicsElementContext::createFillBrush()
{
	Assert(!mFillBrush);
	SafeCall(mParentCanvas->getD2DRenderTarget()->CreateSolidColorBrush(GraphicsConverter::convertToD2D(mFillColor), &mFillBrush));
}
void GraphicsElementContext::createTextFormat()
{
	Assert(!mTextFormat);
	SafeCall(GraphicsManager::getInstance()->getDWriteFactory()->CreateTextFormat(
		L"Arial", NULL, 
		DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		mFontSize, L"en-us", &mTextFormat));
}
void GraphicsElementContext::destroyLineBrush()
{
	Assert(mLineBrush);
	mLineBrush->Release(); mLineBrush = NULL;
}
void GraphicsElementContext::destroyFillBrush()
{
	Assert(mFillBrush);
	mFillBrush->Release(); mFillBrush = NULL;
}
void GraphicsElementContext::destroyTextFormat()
{
	Assert(mTextFormat);
	mTextFormat->Release(); mTextFormat = NULL;
}
