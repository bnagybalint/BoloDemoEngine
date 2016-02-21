#include "RenderSceneElement.h"

#include "Assist/Common.h" 
#include "Assist/Matrix4x4.hpp"
#include "Assist/Matrix3x3.hpp"

#include "Render/RenderCommon.h"
#include "Render/RenderConverter.h"


RenderSceneElement::RenderSceneElement()
	: mWorldTransform(Transform::IDENTITY)
	, mWorldScale(Vector3::UNIT_SCALE)
{
	calculateCachedWorldMatrix();
}


RenderSceneElement::~RenderSceneElement()
{
#if BDE_GLOBAL_ENABLE_NICE_DESTROY
#endif
}

const DirectX::XMVECTOR RenderSceneElement::getDxPosition() const
{
	return RenderConverter::convertToDX(mWorldTransform.getPosition());
}

void RenderSceneElement::calculateCachedWorldMatrix()
{
	Matrix4x4 mx4 = Matrix4x4::createAffineTransform(mWorldTransform.getPosition(), mWorldTransform.getOrientation(), mWorldScale);
	mCachedDxWorldMatrix = RenderConverter::convertToDX(mx4);
}
