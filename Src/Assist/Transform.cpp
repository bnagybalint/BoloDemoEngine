/* ------------------------------------------------ *
 *  Written by:      Nagy Balint                    *
 *  Contact:         b.nagy.balint@gmail.com        *
 *                                                  *
 *  This file can be used/improved/redistributed    *
 *  under GNU public license                        *
 *                                                  *
 *  Nagy Balint (C) 2010                            *
 * ------------------------------------------------ */

#include "Transform.hpp"

#include "Assist/Matrix3x3.hpp"
#include "Assist/Matrix4x4.hpp"

Transform::Transform () { }

Transform::Transform(const Vector3& pos, const Quaternion& ori)
	: mPosition(pos), mOrientation(ori)
{
}

Transform Transform::inverse () const
{
	Quaternion qinv = mOrientation.inverse();
	return Transform(-(qinv*mPosition), qinv);
}

Vector3 Transform::transform (const Vector3& u) const
{
	return mOrientation.transform(u) + mPosition;
}

Matrix4x4 Transform::toMatrix4x4() const
{
	return Matrix4x4::createAffineTransform(mPosition, mOrientation, Vector3::UNIT_SCALE);
}

Transform Transform::operator * (const Transform& tr) const
{
	Quaternion newOri = mOrientation * tr.mOrientation;
	Vector3    newPos = mPosition + mOrientation * tr.mPosition;
	return Transform(newPos, newOri);
}

Vector3 Transform::operator * (const Vector3& u) const
{
	return transform(u);
}

/*static*/Transform Transform::IDENTITY = Transform(Vector3(Coordtype(0.0), Coordtype(0.0), Coordtype(0.0)), Quaternion(Coordtype(1.0), Coordtype(0.0), Coordtype(0.0), Coordtype(0.0)));

