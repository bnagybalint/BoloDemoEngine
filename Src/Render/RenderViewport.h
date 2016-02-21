#pragma once

#include <directxmath.h>

class RenderCamera;

class RenderViewport
{
public:

	RenderViewport( unsigned int width, unsigned int height );
	~RenderViewport();

	void render();

	void setCamera(RenderCamera* camera);

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
	float mFovyDeg;
	float mNearDistance;
	float mFarDistance;

	DirectX::XMMATRIX mCachedDxProjMatrix;
};

