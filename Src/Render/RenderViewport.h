#pragma once

#include "Render/RenderCommon.h"

#include <directxmath.h>

class RenderCamera;

class RenderViewport
{
public:

	RenderViewport();
	~RenderViewport();

	void render();

	void setCamera(RenderCamera* camera);

	void setRectangle(unsigned int minx, unsigned int miny, unsigned int width, unsigned int height);

	void setFOVy(float fovyDeg) { mFovyDeg = fovyDeg; calculateCachedProjMatrix(); }
	void setNearDistance(float neardist) { mNearDistance = neardist; calculateCachedProjMatrix(); }
	void setFarDistance(float fardist) { mFarDistance = fardist; calculateCachedProjMatrix(); }

	const DirectX::XMMATRIX& getDxProjectionMatrix() const { return mCachedDxProjMatrix; }

private:

	void calculateCachedProjMatrix();

private:

	RenderCamera* mCamera;

	unsigned int mWidth;
	unsigned int mHeight;
	unsigned int mTopLeftX;
	unsigned int mTopLeftY;
	float mFovyDeg; // TODO move to camera
	float mNearDistance;
	float mFarDistance;

	DirectX::XMMATRIX mCachedDxProjMatrix;
};

