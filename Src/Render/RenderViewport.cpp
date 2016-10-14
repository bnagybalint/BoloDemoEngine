#include "RenderViewport.h"

#include "Assist/Common.h"
#include "Assist/MathCommon.h"
#include "Assist/Matrix4x4.hpp"

#include "Render/RenderCommon.h"
#include "Render/RenderManager.h"
#include "Render/RenderConverter.h"
#include "Render/RenderCamera.h"

#include <d3d11.h>

RenderViewport::RenderViewport()
	: mCamera(NULL)
	, mWidth(0)
	, mHeight(0)
	, mTopLeftX(0)
	, mTopLeftY(0)
{
}

RenderViewport::~RenderViewport()
{
#if BDE_GLOBAL_ENABLE_NICE_DESTROY
#endif
}

void RenderViewport::render()
{
	if (mCamera)
	{
		mCamera->render(this);
	}
}

void RenderViewport::setCamera(RenderCamera* camera)
{
	mCamera = camera;
}

void RenderViewport::setRectangle(unsigned int minx, unsigned int miny, unsigned int width, unsigned int height)
{
	mWidth = width;
	mHeight = height;
	mTopLeftX = minx;
	mTopLeftY = miny;

	// Setup the viewport for rendering.
	D3D11_VIEWPORT viewport;
	viewport.Width = (float)mWidth;
	viewport.Height = (float)mHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = (float)mTopLeftX;
	viewport.TopLeftY = (float)mTopLeftY;

	// Create the viewport.
	DX_GetDeviceContext(dvc);
	dvc->RSSetViewports(1, &viewport);
}

