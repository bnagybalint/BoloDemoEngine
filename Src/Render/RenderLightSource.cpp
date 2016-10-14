#include "RenderLightSource.h"

#include "Render/RenderCommon.h"
#include "Render/RenderConverter.h"

RenderLightSource::RenderLightSource(RenderScene* scene)
	: RenderSceneElement(scene)
	, mIntensity(Color::WHITE)
	, mAttenuationLinear(0.0f)
	, mAttenuationQuadratic(0.0f)
	, mAttenuationStart(Math::B_NEG_INFINITY)
	, mAttenuationEnd(Math::B_INFINITY)
	, mCutoffAngle(0.0f)
{
}

RenderLightSource::~RenderLightSource()
{
#if BDE_GLOBAL_ENABLE_NICE_DESTROY
#endif
}

void RenderLightSource::lookAt(const Vector3& center, const Vector3& up)
{
	Vector3 ldir = (center - getWorldTransform().getPosition()).getNormalized();
	Vector3 lside = up.cross(ldir); lside.normalize();
	Vector3 lup = ldir.cross(lside); lup.normalize();

	setWorldOrientation(Quaternion::createFromBasis(lside, lup, ldir));
}
