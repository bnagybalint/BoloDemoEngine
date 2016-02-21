#include "RenderLightSource.h"

#include "Render/RenderCommon.h"
#include "Render/RenderConverter.h"

RenderLightSource::RenderLightSource()
	: mDxLightColor(RenderConverter::convertToDX(Vector3(1.0,1.0,1.0,1.0)))
{
}

RenderLightSource::~RenderLightSource()
{
#if BDE_GLOBAL_ENABLE_NICE_DESTROY
#endif
}

void RenderLightSource::lookAt(const Vector3& center, const Vector3& up)
{
	Vector3 ldir = Vector3::normalized(center - getWorldTransform().getPosition());
	Vector3 lside = Vector3::cross(up, ldir); lside.normalize();
	Vector3 lup = Vector3::cross(ldir, lside); lup.normalize();

	setWorldOrientation(Quaternion::createFromAxes(lside, lup, ldir));
}

void RenderLightSource::setColor(const Vector3& color)
{
	mDxLightColor = RenderConverter::convertToDX(color);
}

const DirectX::XMVECTOR RenderLightSource::getDxDirection() const
{
	return RenderConverter::convertToDX(getWorldTransform().getOrientation() * Vector3::UNIT_Z);
}