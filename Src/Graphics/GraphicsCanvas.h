#pragma once

#include "Assist/Common.h"
#include "Assist/Color.h"
#include "Assist/Array.h"
#include "Assist/String.h"
#include "Assist/Vector2.h"

struct ID2D1HwndRenderTarget;

class GraphicsObject;
class GraphicsScene;

class GraphicsCanvas
{
private:

	friend class GraphicsManager;

public:

	void setViewTransform(const Vector2& center, float zoomFactor);
	void setModelTransform(const Vector2& translation, float rotation);

	void draw();

	GraphicsScene* getScene() const { return mScene; }
	void setScene(GraphicsScene* scene) { mScene = scene; }

	ID2D1HwndRenderTarget* getD2DRenderTarget() const { return mRenderTarget; }

	const String& getName() { return mName; }

	const Vector2& getViewCenter() const { return mViewCenter; }
	void setViewCenter(const Vector2& val) { mViewCenter = val; }

	float getZoom() const { return mZoomFactor; }
	void setZoom(float val) { mZoomFactor = val; }

	const Color& getClearColor() const { return mClearColor; }
	void setClearColor(const Color& val) { mClearColor = val; }

private:

	GraphicsCanvas(const String& name, HWND parentWindowHandle);
	DISABLE_COPY(GraphicsCanvas);
	~GraphicsCanvas();

private:

	void createDeviceResources();
	void destroyDeviceResources();

	void updateRenderTargetTransform();

private:

	String mName;

	HWND mWindowHandle;
	ID2D1HwndRenderTarget* mRenderTarget;

	GraphicsScene* mScene;

	// TODO should be perhaps outsourced to GraphicsCamera?
	// Dimensions of the window rectangle in which we render through this canvas
	Vector2 mViewportDimensions;

	// View transform
	Vector2 mViewCenter;
	float mZoomFactor;

	// Modelling transform.
	Vector2 mModelTranslation;
	float mModelRotation; // in radians

	Color mClearColor;
};

