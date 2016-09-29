/* ------------------------------------------------ *
 *  Written by:      Nagy Balint                    *
 *  Contact:         b.nagy.balint@gmail.com        *
 *                                                  *
 *  This file can be used/improved/redistributed    *
 *  under GNU public license                        *
 *                                                  *
 *  Nagy Balint (C) 2015                            *
 * ------------------------------------------------ */

#include "Matrix3x3.hpp"

#include "Assist/Common.h"
#include "Assist/Memory.h"
#include "Assist/MathCommon.h" 
#include "Assist/Vector3.hpp"
#include "Assist/Matrix4x4.hpp"

const Matrix3x3 Matrix3x3::IDENTITY = Matrix3x3(1, 0, 0, 0, 1, 0, 0, 0, 1);
const Matrix3x3 Matrix3x3::ZERO     = Matrix3x3(0, 0, 0, 0, 0, 0, 0, 0, 0);

Matrix3x3::Matrix3x3 () {

	// for debugging purposes, set all values to sNAN
#ifdef BDE_GLOBAL_BUILD_DEBUG 
	for (unsigned int i = 0; i < msNumElements; ++i)
		mx[i] = Math::B_NAN;
#endif
}

Matrix3x3::Matrix3x3 (Coordtype fill)
{
	for (unsigned int i = 0; i < msNumElements; ++i)
		mx[i] = fill;
}

Matrix3x3::Matrix3x3(const Coordtype* data)
{
	Memory::Memcopy(mx, data, msNumElements * sizeof(Coordtype));
}

Matrix3x3::Matrix3x3(
	Coordtype m00, Coordtype m01, Coordtype m02, 
	Coordtype m10, Coordtype m11, Coordtype m12, 
	Coordtype m20, Coordtype m21, Coordtype m22)
{
	mx[mxidx(0, 0)] = m00;
	mx[mxidx(0, 1)] = m01;
	mx[mxidx(0, 2)] = m02;
	mx[mxidx(1, 0)] = m10;
	mx[mxidx(1, 1)] = m11;
	mx[mxidx(1, 2)] = m12;
	mx[mxidx(2, 0)] = m20;
	mx[mxidx(2, 1)] = m21;
	mx[mxidx(2, 2)] = m22;
}

Matrix3x3::Matrix3x3(const MatrixNxN<3>& m)
{
	Memory::Memcopy(mx, m.getData(), msNumElements * sizeof(Coordtype));
}

Matrix3x3::Matrix3x3 (const Matrix3x3& m)
{
	Memory::Memcopy(mx, m.mx, msNumElements * sizeof(Coordtype));
}

Matrix3x3::~Matrix3x3 () {
}

Vector3 Matrix3x3::transform(const Vector3& u) const {
	Coordtype rx = u.x*mx[mxidx(0, 0)] + u.y*mx[mxidx(0, 1)] + u.z*mx[mxidx(0, 2)];
	Coordtype ry = u.x*mx[mxidx(1, 0)] + u.y*mx[mxidx(1, 1)] + u.z*mx[mxidx(1, 2)];
	Coordtype rz = u.x*mx[mxidx(2, 0)] + u.y*mx[mxidx(2, 1)] + u.z*mx[mxidx(2, 2)];
	return Vector3(rx, ry, rz);
}

Vector3 Matrix3x3::transformByTranspose(const Vector3& u) const {
	Coordtype rx = u.x*mx[mxidx(0, 0)] + u.y*mx[mxidx(1, 0)] + u.z*mx[mxidx(2, 0)];
	Coordtype ry = u.x*mx[mxidx(0, 1)] + u.y*mx[mxidx(1, 1)] + u.z*mx[mxidx(2, 1)];
	Coordtype rz = u.x*mx[mxidx(0, 2)] + u.y*mx[mxidx(1, 2)] + u.z*mx[mxidx(2, 2)];
	return Vector3(rx, ry, rz);
}

Matrix3x3 Matrix3x3::inverse() const {
	Coordtype d = determinant();
	Assert(d != 0.0f);

	return Matrix3x3::adjugate() / d;
}

Matrix3x3 Matrix3x3::transpose() const {
	Matrix3x3 r;
	r.mx[0] = mx[0];
	r.mx[1] = mx[3];
	r.mx[2] = mx[6];
	r.mx[3] = mx[1];
	r.mx[4] = mx[4];
	r.mx[5] = mx[7];
	r.mx[6] = mx[2];
	r.mx[7] = mx[5];
	r.mx[8] = mx[8];
	return r;
}

Coordtype Matrix3x3::determinant () const {
	Vector3 a = Vector3(mx[0], -mx[1], mx[2]);
	Vector3 b = Vector3(mx[4] * mx[8] - mx[7] * mx[5], mx[3] * mx[8] - mx[6] * mx[5], mx[3] * mx[7] - mx[6] * mx[4]);
	return a.dot(b);
}

Matrix3x3 Matrix3x3::adjugate() const {
	Matrix3x3 t;
	t.mx[0] = mx[4] * mx[8] - mx[5] * mx[7];
	t.mx[1] = mx[2] * mx[7] - mx[1] * mx[8];
	t.mx[2] = mx[1] * mx[5] - mx[2] * mx[4];
	t.mx[3] = mx[5] * mx[6] - mx[3] * mx[8];
	t.mx[4] = mx[0] * mx[8] - mx[2] * mx[6];
	t.mx[5] = mx[2] * mx[3] - mx[0] * mx[5];
	t.mx[6] = mx[3] * mx[7] - mx[4] * mx[6];
	t.mx[7] = mx[1] * mx[6] - mx[0] * mx[7];
	t.mx[8] = mx[0] * mx[4] - mx[1] * mx[3];
	return t;
}

Matrix3x3 Matrix3x3::orthogonalized() const {
	Unimplemented(); // TODO CHECK
// 	Vector3 z2 = Vector3::cross(mx[0], mx[1], mx[2], mx[3], mx[4], mx[5]).normalize();
// 	Vector3 y2 = Vector3::cross(z2.x, z2.y, z2.z, mx[0], mx[1], mx[2]).normalize();
// 	Vector3 x2 = Vector3::normalized(mx[0], mx[1], mx[2]);
// 
// 	mx[0] = x2.x;
// 	mx[1] = x2.y;
// 	mx[2] = x2.z;
// 	mx[3] = y2.x;
// 	mx[4] = y2.y;
// 	mx[5] = y2.z;
// 	mx[6] = z2.x;
// 	mx[7] = z2.y;
// 	mx[8] = z2.z;
	return *this;
}

Matrix4x4 Matrix3x3::toMatrix4x4() const
{
	return Matrix4x4(
		mx[mxidx(0, 0)], mx[mxidx(0, 1)], mx[mxidx(0, 2)], Coordtype(0),
		mx[mxidx(1, 0)], mx[mxidx(1, 1)], mx[mxidx(1, 2)], Coordtype(0),
		mx[mxidx(2, 0)], mx[mxidx(2, 1)], mx[mxidx(2, 2)], Coordtype(0),
		Coordtype(0),    Coordtype(0),    Coordtype(0),    Coordtype(1)
		);
}

Vector3 Matrix3x3::getRow(unsigned int row) const
{
	Assert(row >= 0 && row <= msNumRows - 1);
	return Vector3(mx[mxidx(row, 0)], mx[mxidx(row, 1)], mx[mxidx(row, 2)]);
}
Vector3 Matrix3x3::getColumn(unsigned int col) const
{
	Assert(col >= 0 && col <= msNumCols - 1);
	return Vector3(mx[mxidx(0, col)], mx[mxidx(1, col)], mx[mxidx(2, col)]);
}

Vector3 Matrix3x3::operator * (const Vector3& u) const
{
	return transform(u);
}

Matrix3x3 Matrix3x3::createScale (const Vector3& s) {

	return Matrix3x3(
		s.x,  0.0f, 0.0f,
		0.0f, s.y,  0.0f,
		0.0f, 0.0f, s.z
		);
}

Matrix3x3 Matrix3x3::createRotationAxisAngle(Coordtype radians, const Vector3& u) {

	Coordtype c = (Coordtype)Math::Cos(radians);
	Coordtype s = (Coordtype)Math::Sin(radians);
	return Matrix3x3(
		u.x*u.x + (1.0f - u.x*u.x)*c, u.y*u.x*(1.0f - c) + u.z*s,   u.z*u.x*(1.0f - c) - u.y*s,
		u.x*u.y*(1.0f - c) - u.z*s,   u.y*u.y + (1.0f - u.y*u.y)*c, u.z*u.y*(1.0f - c) + u.x*s,
		u.x*u.z*(1.0f - c) + u.y*s,   u.y*u.z*(1.0f - c) - u.x*s,   u.z*u.z + (1.0f - u.z*u.z)*c
		);
}

Matrix3x3 Matrix3x3::createFromBasis (const Vector3& u, const Vector3& v, const Vector3& w) {

	return Matrix3x3(
		u.x, v.x, w.x,
		u.y, v.y, w.y,
		u.z, v.z, w.z
		);
}

