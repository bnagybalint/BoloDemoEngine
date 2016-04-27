#pragma once

#include "Assist/Common.h"

#include "Assist/Vector2.h"
#include "Assist/Color.h"

#include "Graphics/GraphicsObject.h"

struct ID2D1SolidColorBrush;

class GraphicsRectangle : public GraphicsObject
{
public:

	GraphicsRectangle();
	DISABLE_COPY(GraphicsRectangle);
	virtual ~GraphicsRectangle();

	const Vector2& getSize() const { return mSize; }
	void setSize(const Vector2& val) { mSize = val; }

	const Color& getFillColor() const { return mFillColor; }
	void setFillColor(const Color& val) { mFillColor = val; }

	const Color& getBorderColor() const { return mBorderColor; }
	void setBorderColor(const Color& val) { mBorderColor = val; }

	float getBorderWidth() const { return mBorderWidth; }
	void setBorderWidth(float val) { mBorderWidth = val; }

	bool getPixelAligned() const { return mPixelAligned; }
	void setPixelAligned(bool val) { mPixelAligned = val; }

private:

	void drawImpl(GraphicsCanvas* target) override;
	void createResourcesImpl(GraphicsCanvas* target) override;
	void destroyResourcesImpl(GraphicsCanvas* target) override;

private:

	Vector2 mSize;
	Color   mFillColor;
	Color   mBorderColor;
	float   mBorderWidth;

	// Is the rectangle's sides and border pixel aligned
	bool    mPixelAligned;

	ID2D1SolidColorBrush* mFillBrush;
	ID2D1SolidColorBrush* mBorderBrush;
};

