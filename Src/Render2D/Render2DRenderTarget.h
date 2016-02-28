#pragma once

#include "Assist/Common.h"
#include "Assist/Array.h"
#include "Assist/Color.h"

#include <string>

struct ID2D1HwndRenderTarget;
struct ID2D1SolidColorBrush;

class Vector2;

class Render2DRenderElement;

class Render2DRenderTarget
{

public:

	Render2DRenderTarget(HWND parentWindowHandle);
	~Render2DRenderTarget();

	ID2D1HwndRenderTarget* getD2DRenderTarget() const { return mRenderTarget; }

	void render();

	void addRenderElement(Render2DRenderElement* element) { mRenderElements.append(element); }
	void removeRenderElement(Render2DRenderElement* element) { mRenderElements.eRemoveUnordered(element); }

public:

	// TODO Create subclasses of Render2DRenderElement instead:
	// - Render2RenderLine
	// - Render2RenderRectangle
	// - Render2RenderText
	void drawLine(const Vector2& v0, const Vector2& v1, float width);
	void drawRectangle(const Vector2& v0, const Vector2& v1, float borderWidth);
	void setLineColor(const Color& color) { mLineColor = color; }
	void setFillColor(const Color& color) { mFillColor = color; }

private:

	void renderItems();
	void sortItems();

	void createDeviceResources();
	void destroyDeviceResources();

private:

	HWND mWindowHandle;
	ID2D1HwndRenderTarget* mRenderTarget;
	ID2D1SolidColorBrush* mBrush; // mLineBrush
	//ID2D1SolidColorBrush* mFillBrush;

	Array<Render2DRenderElement*> mRenderElements;

	Color mFillColor;
	Color mLineColor;
};

