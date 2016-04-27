#include "GraphicsText.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>

#include "Graphics/GraphicsCanvas.h"
#include "Graphics/GraphicsConverter.h"
#include "Graphics/GraphicsManager.h"

GraphicsText::GraphicsText()
	: GraphicsObject()
	, mText("")
	, mTextAlignment(TextAlignment::TopLeft)
	, mTextColor(Color::BLACK)
	, mFontFamily("Arial")
	, mFontSize(12.0f)
	, mTextFormat(NULL)
	, mTextLayout(NULL)
	, mTextBrush(NULL)
	, mProcessedText(NULL)
	, mProcessedTextLength(0)
	, mProcessedFontFamily(NULL)
	, mProcessedFontFamilyLength(0)
	, mProcessedTextDimensions(Vector2::ZERO)
{
}

GraphicsText::~GraphicsText()
{
	destroyText();
	destroyResourcesImpl(NULL);

	if (mProcessedText)
	{
		delete[] mProcessedText; mProcessedText = NULL;
	}
	if (mProcessedFontFamily)
	{
		delete[] mProcessedFontFamily; mProcessedFontFamily = NULL;
	}
}

void GraphicsText::setText(const String& text)
{
	mText = text;
	if(mTextLayout)
		destroyText(); // signal to reconstruct the text object
}

void GraphicsText::setTextAlignment(TextAlignment align)
{
	mTextAlignment = align;
}

void GraphicsText::setFontFamily(const String& family)
{
	mFontFamily = family;

	if (mTextLayout)
	{
		processString(mProcessedFontFamily, mProcessedFontFamilyLength, mFontFamily);
		DWRITE_TEXT_RANGE textRange = { 0, UINT_MAX };
		mTextLayout->SetFontFamilyName(mProcessedFontFamily, textRange);

		layoutText();
	}
}

void GraphicsText::setFontSize(float size)
{
	mFontSize = size;

	if (mTextLayout)
	{
		DWRITE_TEXT_RANGE textRange = { 0, UINT_MAX };
		mTextLayout->SetFontSize(mFontSize, textRange);

		layoutText();
	}
}

void GraphicsText::drawImpl(GraphicsCanvas* target)
{
	if (!mTextLayout)
		createText(); // on-demand creation

	Assert(mTextFormat);
	Assert(mTextLayout);
	Assert(mTextBrush);

	mTextBrush->SetColor(GraphicsConverter::convertToD2D(mTextColor));

	Vector2 alignOffset = calculateAlignmentOffset();
	D2D1_POINT_2F origin = D2D1::Point2F(alignOffset.x, alignOffset.y);
	target->getD2DRenderTarget()->DrawTextLayout(origin, mTextLayout, mTextBrush);

// 	D2D1_RECT_F r = D2D1::RectF(
// 		alignOffset.x,
// 		alignOffset.y,
// 		alignOffset.x + mProcessedTextDimensions.x,
// 		alignOffset.y + mProcessedTextDimensions.y);
// 	target->getD2DRenderTarget()->DrawRectangle(r, mTextBrush);
}

void GraphicsText::createResourcesImpl(GraphicsCanvas* target)
{
	target->getD2DRenderTarget()->CreateSolidColorBrush(GraphicsConverter::convertToD2D(mTextColor), &mTextBrush);
}

void GraphicsText::destroyResourcesImpl(GraphicsCanvas* /*target*/)
{
	Assert(mTextBrush);
	mTextBrush->Release();
	mTextBrush = NULL;
}

void GraphicsText::processString(/*out*/WCHAR*& dstString, /*out*/UINT& dstLength, const String& data)
{
	if (dstString)
	{
		delete[] dstString;
		dstString = NULL;
	}

	dstString = new WCHAR[data.length() + 1];
	mbstowcs(dstString, data.cstr(), data.length() + 1);

	dstLength = (UINT32)data.length();
}

void GraphicsText::createText()
{
	processString(mProcessedFontFamily, mProcessedFontFamilyLength, mFontFamily);
	processString(mProcessedText, mProcessedTextLength, mText);

	SafeCall(GraphicsManager::getInstance()->getDWriteFactory()->CreateTextFormat(
		mProcessedFontFamily, NULL, 
		DWRITE_FONT_WEIGHT_BOLD, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		mFontSize, L"en-us", &mTextFormat));

	SafeCall(GraphicsManager::getInstance()->getDWriteFactory()->CreateTextLayout(
		mProcessedText, mProcessedTextLength, mTextFormat, INFINITY, INFINITY, &mTextLayout
		));

	layoutText();
}

void GraphicsText::destroyText()
{
	Assert(mTextLayout);
	mTextLayout->Release();
	mTextLayout = NULL;
	Assert(mTextFormat);
	mTextFormat->Release();
	mTextFormat = NULL;
}

void GraphicsText::layoutText()
{
	Assert(mTextLayout);

	DWRITE_TEXT_METRICS metrics;
	mTextLayout->GetMetrics(&metrics);

	mProcessedTextDimensions = Vector2(metrics.width, metrics.height);

	mTextLayout->SetMaxWidth(mProcessedTextDimensions.x);
	mTextLayout->SetMaxHeight(mProcessedTextDimensions.y);
}

Vector2 GraphicsText::calculateAlignmentOffset()
{
	float dx = 0.0f;
	float dy = 0.0f;
	switch (mTextAlignment)
	{
	case TextAlignment::TopLeft     : dx = 0.0f; dy = 0.0f; break;
	case TextAlignment::TopCenter   : dx =-0.5f; dy = 0.0f; break;
	case TextAlignment::TopRight    : dx =-1.0f; dy = 0.0f; break;
	case TextAlignment::MidLeft     : dx = 0.0f; dy =-0.5f; break;
	case TextAlignment::MidCenter   : dx =-0.5f; dy =-0.5f; break;
	case TextAlignment::MidRight    : dx =-1.0f; dy =-0.5f; break;
	case TextAlignment::BottomLeft  : dx = 0.0f; dy =-1.0f; break;
	case TextAlignment::BottomCenter: dx =-0.5f; dy =-1.0f; break;
	case TextAlignment::BottomRight : dx =-1.0f; dy =-1.0f; break;
	default: Unimplemented(); break;
	}

	return Vector2(mProcessedTextDimensions.x * dx, mProcessedTextDimensions.y * dy);
}
