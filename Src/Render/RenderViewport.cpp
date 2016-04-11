#include "RenderViewport.h"

#include "Assist/Common.h"
#include "Assist/MathCommon.h"

#include "Render/RenderManager.h"

#include <d3d11.h>

RenderViewport::RenderViewport()
	: mCamera(NULL)
	, mWidth(0)
	, mHeight(0)
	, mTopLeftX(0)
	, mTopLeftY(0)
	, mFovyDeg(50.0f)
	, mNearDistance(0.1f)
	, mFarDistance(100.0f)
	, mCachedDxProjMatrix()
{
}

RenderViewport::~RenderViewport()
{
#if BDE_GLOBAL_ENABLE_NICE_DESTROY
#endif
}

void RenderViewport::render()
{
	Unimplemented();
}

void RenderViewport::setCamera(RenderCamera* camera)
{
	mCamera = camera;
}

void RenderViewport::setRectangle(unsigned int minx, unsigned int miny, unsigned int width, unsigned int height)
{
	// Setup the viewport for rendering.
	D3D11_VIEWPORT viewport;
	viewport.Width = (float)width;
	viewport.Height = (float)height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = (float)minx;
	viewport.TopLeftY = (float)miny;

	// Create the viewport.
	DX_GetDeviceContext(dvc);
	dvc->RSSetViewports(1, &viewport);

	calculateCachedProjMatrix();
}

void RenderViewport::calculateCachedProjMatrix()
{
	mCachedDxProjMatrix = DirectX::XMMatrixPerspectiveFovLH(Math::Deg2Rad(mFovyDeg), float(mWidth) / float(mHeight), mNearDistance, mFarDistance);
}
