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

Transform& Transform::inverse ()
{
   mOrientation.inverse();
   mPosition = -mPosition;
   return *this;
}

Transform Transform::inverse (const Transform& transform)
{
	Quaternion qinv = Quaternion::inverse(transform.mOrientation);
	return Transform(-(qinv*transform.mPosition), qinv);
}

Vector3 Transform::transform (const Vector3& u) const
{
   return mOrientation.transform(u) + mPosition;
}

Matrix4x4 Transform::toMatrix4x4() const
{
	Matrix4x4 rv;
	rv.makeFromParts(mOrientation.toMatrix3x3(), mPosition, Vector3::ZERO, Coordtype(0));
	return rv;
}

/*static*/Transform Transform::IDENTITY = Transform(Vector3(Coordtype(0.0), Coordtype(0.0), Coordtype(0.0)), Quaternion(Coordtype(1.0), Coordtype(0.0), Coordtype(0.0), Coordtype(0.0)));

