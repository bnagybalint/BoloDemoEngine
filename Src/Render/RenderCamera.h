#pragma once

#include "Assist/Common.h"

#include "Assist/Plane.hpp"

#include "Render/RenderSceneElement.h"

class RenderScene;
class RenderViewport;

class RenderCamera : public RenderSceneElement
{
	// Forward direction is local +z
	// Up direction is local +y

public:
	RenderCamera(RenderScene* scene);
	~RenderCamera();

	void render(RenderViewport* vp);

	void getFrustumPlanes(/*out*/Plane& pLeft, /*out*/Plane& pRight, /*out*/Plane& pBottom, /*out*/Plane& pTop, /*out*/Plane& pNear, /*out*/Plane& pFar) const;

	void setCameraAxes(const Vector3& dir, const Vector3& up);

	float getFovY() const { return mFovy; }
	void setFovY(float fovyRad) { mFovy = fovyRad; }
	float getNearDistance() const { return mNearDistance; }
	void setNearDistance(float val) { mNearDistance = val; }
	float getFarDistance() const { return mFarDistance; }
	void setFarDistance(float val) { mFarDistance = val; }

private:
	float mFovy; // radians
	float mNearDistance;
	float mFarDistance;

	// -----------------------------
};

