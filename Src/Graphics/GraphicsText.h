#pragma once

#include "Assist/Common.h"
#include "Assist/String.h"
#include "Assist/Color.h"
#include "Assist/Vector2.h"

#include "Graphics/GraphicsObject.h"

struct IDWriteTextFormat;
struct IDWriteTextLayout;
struct ID2D1SolidColorBrush;

class GraphicsText : public GraphicsObject
{
public:

	EnumBegin(TextAlignment, TopLeft)
		TopLeft,
		TopCenter,
		TopRight,
		MidLeft,
		MidCenter,
		MidRight,
		BottomLeft,
		BottomCenter,
		BottomRight,
	EnumEnd(TextAlignment)

public:

	GraphicsText();
	DISABLE_COPY(GraphicsText);
	~GraphicsText();

	Vector2 getPreferredSize() const;

	const String& getText() const { return mText; }
	void setText(const String& text);

	TextAlignment getTextAlignment() const { return mTextAlignment; }
	void setTextAlignment(TextAlignment align);

	const Color& getTextColor() const { return mTextColor; }
	void setTextColor(const Color& color) { mTextColor = color; }

	const String& getFontFamily() const { return mFontFamily; }
	void setFontFamily(const String& family);

	float getFontSize() const { return mFontSize; }
	void setFontSize(float size);

private:

	void drawImpl(GraphicsCanvas* target) override;
	void createResourcesImpl(GraphicsCanvas* target) override;
	void destroyResourcesImpl(GraphicsCanvas* target) override;

	void processString(/*out*/WCHAR*& dstString, /*out*/UINT& dstLength, const String& data);

	void createText();
	void layoutText();
	void destroyText();

	Vector2 calculateAlignmentOffset();

private:

	String mText;

	TextAlignment mTextAlignment;
	Color mTextColor;
	String mFontFamily;
	float mFontSize;

	IDWriteTextFormat* mTextFormat;
	IDWriteTextLayout* mTextLayout;
	ID2D1SolidColorBrush* mTextBrush;

	WCHAR*  mProcessedText;
	UINT    mProcessedTextLength;
	WCHAR*  mProcessedFontFamily;
	UINT    mProcessedFontFamilyLength;
	Vector2 mProcessedTextDimensions;
};

