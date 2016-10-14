#include "RenderSceneElement.h"

#include "Assist/Common.h" 
#include "Assist/Matrix4x4.hpp"
#include "Assist/Matrix3x3.hpp"

#include "Render/RenderCommon.h"
#include "Render/RenderConverter.h"
#include "Render/RenderScene.h"


RenderSceneElement::RenderSceneElement(RenderScene* scene)
	: mScene(scene)
	, mWorldTransform(Transform::IDENTITY)
	, mWorldScale(Vector3::UNIT_SCALE)
{
	Assert(scene);
}

RenderSceneElement::~RenderSceneElement()
{
#if BDE_GLOBAL_ENABLE_NICE_DESTROY
#endif
}

DirectX::XMMATRIX RenderSceneElement::getDxWorldMatrix() const
{
	Matrix4x4 mx4 = Matrix4x4::createAffineTransform(mWorldTransform.getPosition(), mWorldTransform.getOrientation(), mWorldScale);
	return RenderConverter::convertToDX(mx4);
}

DirectX::XMVECTOR RenderSceneElement::getDxPosition() const
{
	return RenderConverter::convertToDX(mWorldTransform.getPosition());
}
