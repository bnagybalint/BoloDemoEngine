#include "RenderViewport.h"

#include "Assist/Common.h"
#include "Assist/MathCommon.h"

RenderViewport::RenderViewport( unsigned int width, unsigned int height )
	: mWidth(width)
	, mHeight(height)
	, mFovyDeg(50.0f)
	, mNearDistance(0.1f)
	, mFarDistance(100.0f)
{
	calculateCachedProjMatrix();
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

void RenderViewport::calculateCachedProjMatrix()
{
	mCachedDxProjMatrix = DirectX::XMMatrixPerspectiveFovLH(Math::Deg2Rad(mFovyDeg), float(mWidth) / float(mHeight), mNearDistance, mFarDistance);
}
