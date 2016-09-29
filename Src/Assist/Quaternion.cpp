/* ------------------------------------------------ *
 *  Written by:      Nagy Balint                    *
 *  Contact:         b.nagy.balint@gmail.com        *
 *                                                  *
 *  This file can be used/improved/redistributew    *
 *  under GNU publiz license                        *
 *                                                  *
 *  Nagy Balint (C) 2010                            *
 * ------------------------------------------------ */

#include "Quaternion.hpp"

#include "Assist/MathCommon.h"
#include "Assist/Vector3.hpp"
#include "Assist/Matrix3x3.hpp"
#include "Assist/Matrix4x4.hpp"

/*static*/Quaternion Quaternion::IDENTITY = Quaternion(Coordtype(1.0), Coordtype(0.0), Coordtype(0.0), Coordtype(0.0));

Quaternion::Quaternion () :
	w(q[0]), x(q[1]), y(q[2]), z(q[3]) {

	// for debugging purposes, set all values to sNAN
#ifdef BDE_GLOBAL_BUILD_DEBUG 
	w = Math::B_NAN;
	x = Math::B_NAN;
	y = Math::B_NAN;
	z = Math::B_NAN;
#endif
}

Quaternion::Quaternion (Coordtype w0, Coordtype x0, Coordtype y0, Coordtype z0) :
	w(q[0]), x(q[1]), y(q[2]), z(q[3]) {

	x = x0;
	y = y0;
	z = z0;
	w = w0;
}

Quaternion::Quaternion (Coordtype w0, const Vector3& vec) :
w(q[0]), x(q[1]), y(q[2]), z(q[3]) {

	w = w0;
	x = vec.x;
	y = vec.y;
	z = vec.z;
}

Quaternion::Quaternion (const Quaternion& other) :
	w(q[0]), x(q[1]), y(q[2]), z(q[3]) {

	w = other.w;
	x = other.x;
	y = other.y;
	z = other.z;
}

Quaternion::~Quaternion () {
}

Quaternion Quaternion::sum (const Quaternion& q) const {
	return Quaternion(w + q.w, x + q.x, y + q.y, z + q.z);
}

Quaternion Quaternion::subtract(const Quaternion& q) const {
	return Quaternion(w - q.w, x - q.x, y - q.y, z - q.z);
}

Coordtype Quaternion::dot(const Quaternion& q) const {
	return w * q.w + x * q.x + y * q.y + z * q.z;
}

Quaternion Quaternion::multiply(const Quaternion& q) const {
	Coordtype xr = w * q.w - x * q.x - y * q.y - z * q.z;
	Coordtype yr = w * q.x + x * q.w + y * q.z - z * q.y;
	Coordtype zr = w * q.y - x * q.z + y * q.w + z * q.x;
	Coordtype wr = w * q.z + x * q.y - y * q.x + z * q.w;
	return Quaternion(xr, yr, zr, wr);
}

Coordtype Quaternion::length () const {
	return Math::Sqrt(w * w + x * x + y * y + z * z);
}

Coordtype Quaternion::lengthSquared () const {
	return w * w + x * x + y * y + z * z;
}

Quaternion Quaternion::normalize () const {
	Coordtype l = length();
	return Quaternion(w / l, x / l, y / l, z / l);
}

Quaternion Quaternion::conjugate () const {
	return Quaternion(w, -x, -y, -z);
}

Vector3 Quaternion::transform(const Vector3& v) const {
	return toMatrix3x3().transform(v);
}

Quaternion Quaternion::inverse () const {
	Coordtype l2 = lengthSquared();
	return Quaternion(w / l2, -x / l2, -y / l2, -z / l2);
}

Quaternion& Quaternion::operator = (const Quaternion& q) {
	w = q.w;
	x = q.x;
	y = q.y;
	z = q.z;
	return *this;
}

bool Quaternion::operator == (const Quaternion& q) const {
	return w == q.w && x == q.x && y == q.y && z == q.z;
}

bool Quaternion::operator != (const Quaternion& q) const {
	return w != q.w || x != q.x || y != q.y || z != q.z;
}

bool Quaternion::operator < (const Quaternion& q) const {
	(void)q;
	// TODO
	return true;
}

Quaternion Quaternion::operator - () const {
	return Quaternion(w, -x, -y, -z);
}

Quaternion Quaternion::operator + (const Quaternion& q) const {
	return Quaternion(w + q.w, x + q.x, y + q.y, z + q.z);
}

Quaternion Quaternion::operator - (const Quaternion& q) const {
	return Quaternion(w - q.w, x - q.x, y - q.y, z - q.z);
}

Quaternion Quaternion::operator * (const Quaternion& q) const {
	Coordtype xr = w * q.w - x * q.x - y * q.y - z * q.z;
	Coordtype yr = w * q.x + x * q.w + y * q.z - z * q.y;
	Coordtype zr = w * q.y - x * q.z + y * q.w + z * q.x;
	Coordtype wr = w * q.z + x * q.y - y * q.x + z * q.w;
	return Quaternion(xr, yr, zr, wr);
}

Vector3 Quaternion::operator *  (const Vector3& v) const {
	return transform(v);
}

Quaternion Quaternion::operator * (Coordtype lambda) const {
	return Quaternion(w * lambda, x * lambda, y * lambda, z * lambda);
}

Quaternion Quaternion::operator / (Coordtype lambda) const {
	return Quaternion(w / lambda, x / lambda, y / lambda, z / lambda);
}

Quaternion& Quaternion::operator += (const Quaternion& q) {
	w += q.w;
	x += q.x;
	y += q.y;
	z += q.z;
	return *this;
}

Quaternion& Quaternion::operator -= (const Quaternion& q) {
	w -= q.w;
	x -= q.x;
	y -= q.y;
	z -= q.z;
	return *this;
}

Quaternion& Quaternion::operator *= (Coordtype lambda) {
	w *= lambda;
	x *= lambda;
	y *= lambda;
	z *= lambda;
	return *this;
}

Quaternion& Quaternion::operator /= (Coordtype lambda) {
	w /= lambda;
	x /= lambda;
	y /= lambda;
	z /= lambda;
	return *this;
}

Quaternion::operator const Coordtype* () const {
	return q;
}

Coordtype Quaternion::getAngle () const {
	return w;
}

Vector3 Quaternion::getAxis () const {
	return Vector3(x, y, z);
}

void Quaternion::setAngle (Coordtype r) {
	w = r;
}

void Quaternion::setAxis (const Vector3& v) {
	x = v.x;
	y = v.y;
	z = v.z;
}

Matrix3x3 Quaternion::toMatrix3x3 () const {
	// FIXME check if correct
	Matrix3x3 ret;
	ret(0,0) = 1.0f - 2.0f*(y*y + z*z);
	ret(0,1) = 2.0f*(x*y - z*w);
	ret(0,2) = 2.0f*(x*z + y*w);

	ret(1,0) = 2.0f*(x*y + z*w);
	ret(1,1) = 1.0f - 2.0f*(x*x + z*z);
	ret(1,2) = 2.0f*(y*z - x*w);

	ret(2,0) = 2.0f*(x*z - y*w);
	ret(2,1) = 2.0f*(y*z + x*w);
	ret(2,2) = 1.0f - 2.0f*(x*x + y*y);

	return ret;
}

Matrix4x4 Quaternion::toMatrix4x4 () const {
	// FIXME check if correct
	Matrix4x4 ret;
	ret(0,0) = 1.0f - 2.0f*(y*y + z*z);
	ret(0,1) = 2.0f*(x*y - z*w);
	ret(0,2) = 2.0f*(x*z + y*w);
	ret(0,3) = 0.0f;

	ret(1,0) = 2.0f*(x*y + z*w);
	ret(1,1) = 1.0f - 2.0f*(x*x + z*z);
	ret(1,2) = 2.0f*(y*z - x*w);
	ret(1,3) = 0.0f;

	ret(2,0) = 2.0f*(x*z - y*w);
	ret(2,1) = 2.0f*(y*z + x*w);
	ret(2,2) = 1.0f - 2.0f*(x*x + y*y);
	ret(2,3) = 0.0f;

	ret(3,0) = 0.0f;
	ret(3,1) = 0.0f;
	ret(3,2) = 0.0f;
	ret(3,3) = 1.0f;

	return ret;
}

/*static*/Quaternion Quaternion::createFromAxisAngle(Coordtype radians, const Vector3& axis) {
	return Quaternion(Math::Cos(radians), axis * Math::Sin(radians));
}

/*static*/Quaternion Quaternion::createFromBasis(const Vector3& x, const Vector3& y, const Vector3& z)
{
	// From: J.M.P. van Waveren: From Quaternion to Matrix and Back, 2005, Id Software

	Coordtype m[3][3] = {
// 		{ x.x, y.x, z.x },
// 		{ x.y, y.y, z.y },
// 		{ x.z, y.z, z.z },

		{ x.x, x.y, x.z },
		{ y.x, y.y, y.z },
		{ z.x, z.y, z.z },
	};

	size_t k[4];
	Coordtype sign[3];

	if (m[0][0] + m[1][1] + m[2][2] > 0.0f)
	{
		k[0] = 3; k[1] = 2; k[2] = 1; k[3] = 0;
		sign[0] = 1.0f; sign[1] = 1.0f; sign[2] = 1.0f;
	}
	else if (m[0][0] > m[1][1] && m[0][0] > m[2][2])
	{
		k[0] = 0; k[1] = 1; k[2] = 2;  k[3] = 3;
		sign[0] = 1.0f; sign[1] = -1.0f; sign[2] = -1.0f;
	}
	else if (m[1][1] > m[2][2])
	{
		k[0] = 1; k[1] = 0; k[2] = 3;  k[3] = 2;
		sign[0] = -1.0f; sign[1] = 1.0f; sign[2] = -1.0f;
	}
	else
	{
		k[0] = 2; k[1] = 3; k[2] = 0;  k[3] = 1;
		sign[0] = -1.0f; sign[1] = -1.0f; sign[2] = 1.0f;
	}

	Coordtype t = sign[0] * m[0][0] + sign[1] * m[1][1] + sign[2] * m[2][2] + 1.0f;
	Coordtype s = 1.0f / Math::Sqrt(t) * 0.5f;

	Coordtype q[4];
	q[k[0]] = s * t;
	q[k[1]] = (m[0][1] - sign[2] * m[1][0]) * s;
	q[k[2]] = (m[2][0] - sign[1] * m[0][2]) * s;
	q[k[3]] = (m[1][2] - sign[0] * m[2][1]) * s;

	return Quaternion(q[3], q[0], q[1], q[2]);
}

