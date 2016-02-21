#include "RenderCamera.h"

#include "Assist/Common.h"
#include "Assist/Matrix3x3.hpp"
#include "Assist/Matrix4x4.hpp"

#include "Render/RenderCommon.h"
#include "Render/RenderConverter.h"

#include <directxmath.h>

RenderCamera::RenderCamera()
{
}


RenderCamera::~RenderCamera()
{
#if BDE_GLOBAL_ENABLE_NICE_DESTROY
#endif
}

DirectX::XMMATRIX RenderCamera::getDxViewMatrix() const
{
// 	Assert(Math::Abs(getWorldScale().x - 1.0f) < 1e-3f); // no scale allowed
// 	Assert(Math::Abs(getWorldScale().y - 1.0f) < 1e-3f); // no scale allowed
// 	Assert(Math::Abs(getWorldScale().z - 1.0f) < 1e-3f); // no scale allowed
// 
// 	const Transform& cTrans = getWorldTransform();
// 	Matrix3x3 cOri = cTrans.getOrientation().toMatrix3x3();
// 
// 	Vector3 cPos = cTrans.getPosition();
// 	Vector3 cAt = cPos + cOri.getColumn(2);
// 	Vector3 cUp = cOri.getColumn(1);
// 
// 	return DirectX::XMMatrixLookAtRH(
// 		RenderConverter::convertToDX(cPos),
// 		RenderConverter::convertToDX(cAt),
// 		RenderConverter::convertToDX(cUp));


	Assert(Math::Abs(getWorldScale().x - 1.0f) < 1e-3f); // no scale allowed
	Assert(Math::Abs(getWorldScale().y - 1.0f) < 1e-3f); // no scale allowed
	Assert(Math::Abs(getWorldScale().z - 1.0f) < 1e-3f); // no scale allowed

	const Transform& cTrans = getWorldTransform();
	Matrix3x3 cOri = cTrans.getOrientation().toMatrix3x3();

	Vector3 cPos = cTrans.getPosition();
	Vector3 cAt = cPos + cOri.getColumn(2);
	Vector3 cUp = cOri.getColumn(1);

	cAt.z *= -1.0;
	cPos.z *= -1.0;

	DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(RenderConverter::convertToDX(cPos),RenderConverter::convertToDX(cAt),RenderConverter::convertToDX(cUp));
	DirectX::XMMATRIX invy = DirectX::XMMatrixScaling(1, 1, -1);
	return DirectX::XMMatrixMultiply(invy,view);
}


void RenderCamera::setCameraAxes(const Vector3& dir, const Vector3& up)
{
	mUpVector = up;
	mDirection = dir;
	calculateBasis();
}

void RenderCamera::roll(float angleRad)
{
	mUpVector.rotate(mDirection, angleRad);
	calculateBasis();
}

void RenderCamera::pitch(float angleRad)
{
	mDirection.rotate(mUpVector, angleRad);
	calculateBasis();
}

void RenderCamera::yaw(float angleRad)
{
	const Vector3 right = getRight();
	mUpVector.rotate(right, angleRad);
	mDirection.rotate(right, angleRad);
	calculateBasis();
}

void RenderCamera::calculateBasis()
{
	mDirection.normalize();
	mUpVector = Vector3::cross(mDirection, getRight());
	mUpVector.normalize();

	Vector3 z = mDirection;
	Vector3 x = getRight();
	Vector3 y = mUpVector;

	setWorldOrientation(Quaternion::createFromAxes(x, y, z));
}

Vector3 RenderCamera::getRight() const
{
	return Vector3::normalized(Vector3::cross(mUpVector, mDirection));
}

