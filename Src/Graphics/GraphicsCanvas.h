#pragma once

#include "Assist/Common.h"
#include "Assist/Color.h"
#include "Assist/Array.h"
#include "Assist/String.h"

struct ID2D1HwndRenderTarget;

class GraphicsObject;

class GraphicsCanvas
{
private:

	friend class GraphicsManager;

public:

	void draw();

	GraphicsObject* createGraphicsObject();
	void destroyGraphicsObject(GraphicsObject* obj);

	void setClearColor(const Color& color) { mClearColor = color; }

	ID2D1HwndRenderTarget* getD2DRenderTarget() const { return mRenderTarget; }

	const String& getName() { return mName; }

private:

	GraphicsCanvas(const String& name, HWND parentWindowHandle);
	DISABLE_COPY(GraphicsCanvas);
	~GraphicsCanvas();

private:

	void drawObjects();
	void sortObjects();

	void createDeviceResources();
	void destroyDeviceResources();

private:

	String mName;

	HWND mWindowHandle;
	ID2D1HwndRenderTarget* mRenderTarget;

	Color mClearColor;

	Array<GraphicsObject*> mObjectList;
	bool mObjectListDirty;
};

