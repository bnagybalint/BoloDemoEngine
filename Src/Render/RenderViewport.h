#pragma once

#include "Assist/Common.h"

#include "Render/RenderCommon.h"

class RenderCamera;

class RenderViewport
{
public:

	RenderViewport();
	~RenderViewport();

	void render();

	void setCamera(RenderCamera* camera);

	void setRectangle(unsigned int minx, unsigned int miny, unsigned int width, unsigned int height);

	unsigned int getWidth() const { return mWidth; }
	void setWidth(unsigned int val) { mWidth = val; }
	unsigned int getHeight() const { return mHeight; }
	void setHeight(unsigned int val) { mHeight = val; }

private:

	RenderCamera* mCamera;

	unsigned int mWidth;
	unsigned int mHeight;
	unsigned int mTopLeftX;
	unsigned int mTopLeftY;
};

