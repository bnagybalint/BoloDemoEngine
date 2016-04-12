#pragma once

#include "Assist/Common.h"
#include "Assist/String.h"
#include "Assist/Color.h"

struct ID2D1HwndRenderTarget;
struct ID2D1SolidColorBrush;
struct IDWriteTextFormat;

class GraphicsCanvas;

class GraphicsElementContext
{
public:

	EnumBegin(TextAlignment, Left)
		Left,
		Center,
		Right,
		Justified,
		EnumEnd(TextAlignment)

public:

	GraphicsElementContext(GraphicsCanvas* parentCanvas);
	~GraphicsElementContext();

	void setLineColor(const Color& c);
	void setLineWidth(float w);
	void setFillColor(const Color& c);
	void setFontFamily(const String& name);
	void setFontSize(float size);
	void setTextAlignment(const TextAlignment& align);

	const Color& getLineColor() const { return mLineColor; }
	float getLineWidth() const { return mLineWidth; }
	const Color& getFillColor() const { return mFillColor; }
	const String& getFontFamily() const { return mFontFamily; }
	float getFontSize() const { return mFontSize; }
	const TextAlignment& getTextAlignment() const { return mTextAlignment; }

	ID2D1SolidColorBrush* getLineBrush();
	ID2D1SolidColorBrush* getFillBrush();
	IDWriteTextFormat*    getTextFormat();

private:

	void createLineBrush();
	void createFillBrush();
	void createTextFormat();

	void destroyLineBrush();
	void destroyFillBrush();
	void destroyTextFormat();

private:

	GraphicsCanvas* mParentCanvas;

	Color         mLineColor;
	float         mLineWidth;
	Color         mFillColor;
	String        mFontFamily;
	float         mFontSize;
	TextAlignment mTextAlignment;

	ID2D1SolidColorBrush* mLineBrush;
	ID2D1SolidColorBrush* mFillBrush;
	IDWriteTextFormat*    mTextFormat;
};

