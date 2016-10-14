#include "RenderCamera.h"

#include "Assist/Common.h"

#include "Render/RenderCommon.h"
#include "Render/RenderScene.h"

RenderCamera::RenderCamera(RenderScene* scene)
	: RenderSceneElement(scene)
	, mFovy(Math::Deg2Rad(90.0f))
	, mNearDistance(1.0f)
	, mFarDistance(100.0f)
{
}

RenderCamera::~RenderCamera()
{
#if BDE_GLOBAL_ENABLE_NICE_DESTROY
#endif
}

void RenderCamera::render(RenderViewport* vp)
{
	getScene()->render(vp, this);
}

void RenderCamera::setCameraAxes(const Vector3& dir, const Vector3& up)
{
	Vector3 z = dir;    z.normalize();
	Vector3 x = up % z; x.normalize();
	Vector3 y = z % x;
	setWorldOrientation(Quaternion::createFromBasis(x, y, z));
}

