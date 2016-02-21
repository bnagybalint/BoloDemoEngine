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

Matrix3x3::Matrix3x3 () {}

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
	mx[mxidx(1, 0)] = m01;
	mx[mxidx(2, 0)] = m02;
	mx[mxidx(0, 1)] = m10;
	mx[mxidx(1, 1)] = m11;
	mx[mxidx(2, 1)] = m12;
	mx[mxidx(0, 2)] = m20;
	mx[mxidx(1, 2)] = m21;
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
	return Matrix3x3::transform(*this, u);
}

Vector3 Matrix3x3::transform(const Matrix3x3& m, const Vector3& u) {
	Coordtype rx = u.x*m.mx[mxidx(0, 0)] + u.y*m.mx[mxidx(0, 1)] + u.z*m.mx[mxidx(0, 2)];
	Coordtype ry = u.x*m.mx[mxidx(1, 0)] + u.y*m.mx[mxidx(1, 1)] + u.z*m.mx[mxidx(1, 2)];
	Coordtype rz = u.x*m.mx[mxidx(2, 0)] + u.y*m.mx[mxidx(2, 1)] + u.z*m.mx[mxidx(2, 2)];
	return Vector3(rx, ry, rz);
}

Vector3 Matrix3x3::transformByTranspose(const Vector3& u) const {
	return Matrix3x3::transformByTranspose(*this, u);
}

Vector3 Matrix3x3::transformByTranspose(const Matrix3x3& m, const Vector3& u) {
	Coordtype rx = u.x*m.mx[mxidx(0, 0)] + u.y*m.mx[mxidx(1, 0)] + u.z*m.mx[mxidx(2, 0)];
	Coordtype ry = u.x*m.mx[mxidx(0, 1)] + u.y*m.mx[mxidx(1, 1)] + u.z*m.mx[mxidx(2, 1)];
	Coordtype rz = u.x*m.mx[mxidx(0, 2)] + u.y*m.mx[mxidx(1, 2)] + u.z*m.mx[mxidx(2, 2)];
	return Vector3(rx, ry, rz);
}

Matrix3x3& Matrix3x3::inverse () {
   Coordtype d = this->determinant();
   Assert (d != 0.0f);

   adjugate();
   for (int i = 0; i < msNumElements; i++) {
      mx[i] /= d;
   }

   return *this;
}

Matrix3x3 Matrix3x3::inverse (const Matrix3x3& m) {
   Coordtype d = m.determinant();
   Assert (d != 0.0f);

   return Matrix3x3::adjugate(m) / d;
}

Matrix3x3& Matrix3x3::transpose () {
   Memory::Swap(mx[1], mx[3]);
   Memory::Swap(mx[2], mx[6]);
   Memory::Swap(mx[5], mx[7]);
   return *this;
}

Matrix3x3 Matrix3x3::transpose (const Matrix3x3& m) {
   Matrix3x3 r;
   r.mx[0] = m.mx[0];
   r.mx[1] = m.mx[3];
   r.mx[2] = m.mx[6];
   r.mx[3] = m.mx[1];
   r.mx[4] = m.mx[4];
   r.mx[5] = m.mx[7];
   r.mx[6] = m.mx[2];
   r.mx[7] = m.mx[5];
   r.mx[8] = m.mx[8];
   return r;
}

Coordtype Matrix3x3::determinant () const {
   Vector3 a = Vector3(mx[0], -mx[1], mx[2]);
   Vector3 b = Vector3(mx[4] * mx[8] - mx[7] * mx[5], mx[3] * mx[8] - mx[6] * mx[5], mx[3] * mx[7] - mx[6] * mx[4]);
   return a.dot(b);
}

Coordtype Matrix3x3::determinant(const Matrix3x3& m) {
   return m.determinant();
}

Matrix3x3& Matrix3x3::adjugate() {
   Matrix3x3 t(*this);
   mx[0] = t.mx[4] * t.mx[8] - t.mx[5] * t.mx[7];
   mx[3] = t.mx[5] * t.mx[6] - t.mx[3] * t.mx[8];
   mx[6] = t.mx[3] * t.mx[7] - t.mx[4] * t.mx[6];
   mx[1] = t.mx[2] * t.mx[7] - t.mx[1] * t.mx[8];
   mx[4] = t.mx[0] * t.mx[8] - t.mx[2] * t.mx[6];
   mx[7] = t.mx[1] * t.mx[6] - t.mx[0] * t.mx[7];
   mx[2] = t.mx[1] * t.mx[5] - t.mx[2] * t.mx[4];
   mx[5] = t.mx[2] * t.mx[3] - t.mx[0] * t.mx[5];
   mx[8] = t.mx[0] * t.mx[4] - t.mx[1] * t.mx[3];
   return *this;
}

Matrix3x3 Matrix3x3::adjugate(const Matrix3x3& m) {
   Matrix3x3 t;
   t.mx[0] = m.mx[4] * m.mx[8] - m.mx[5] * m.mx[7];
   t.mx[1] = m.mx[2] * m.mx[7] - m.mx[1] * m.mx[8];
   t.mx[2] = m.mx[1] * m.mx[5] - m.mx[2] * m.mx[4];
   t.mx[3] = m.mx[5] * m.mx[6] - m.mx[3] * m.mx[8];
   t.mx[4] = m.mx[0] * m.mx[8] - m.mx[2] * m.mx[6];
   t.mx[5] = m.mx[2] * m.mx[3] - m.mx[0] * m.mx[5];
   t.mx[6] = m.mx[3] * m.mx[7] - m.mx[4] * m.mx[6];
   t.mx[7] = m.mx[1] * m.mx[6] - m.mx[0] * m.mx[7];
   t.mx[8] = m.mx[0] * m.mx[4] - m.mx[1] * m.mx[3];
   return t;
}

Matrix3x3& Matrix3x3::orthogonalize() {
	Unimplemented(); // TODO CHECK
	Vector3 z2 = Vector3::cross(mx[0], mx[1], mx[2], mx[3], mx[4], mx[5]).normalize();
	Vector3 y2 = Vector3::cross(z2.x, z2.y, z2.z, mx[0], mx[1], mx[2]).normalize();
	Vector3 x2 = Vector3::normalized(mx[0], mx[1], mx[2]);

	mx[0] = x2.x;
	mx[1] = x2.y;
	mx[2] = x2.z;
	mx[3] = y2.x;
	mx[4] = y2.y;
	mx[5] = y2.z;
	mx[6] = z2.x;
	mx[7] = z2.y;
	mx[8] = z2.z;

	return *this;
}

Matrix3x3 Matrix3x3::orthogonalize(const Matrix3x3& m) {
	Matrix3x3 res = m;
	res.orthogonalize();
	return res;
}

Matrix4x4 Matrix3x3::toMatrix4x4() const
{
	Matrix4x4 rv = Matrix4x4::IDENTITY;
	rv(0, 0) = mx[mxidx(0,0)];
	rv(0, 1) = mx[mxidx(0,1)];
	rv(0, 2) = mx[mxidx(0,2)];
	rv(0, 3) = Coordtype(0);
	rv(1, 0) = mx[mxidx(1, 0)];
	rv(1, 1) = mx[mxidx(1, 1)];
	rv(1, 2) = mx[mxidx(1, 2)];
	rv(1, 3) = Coordtype(0);
	rv(2, 0) = mx[mxidx(2, 0)];
	rv(2, 1) = mx[mxidx(2, 1)];
	rv(2, 2) = mx[mxidx(2, 2)];
	rv(2, 3) = Coordtype(0);
	rv(3, 0) = Coordtype(0);
	rv(3, 1) = Coordtype(0);
	rv(3, 2) = Coordtype(0);
	rv(3, 3) = Coordtype(1);
	return rv;
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

Matrix3x3 Matrix3x3::createFromScale (const Vector3& s) {

	Coordtype m[msNumElements] = {
      s.x,  0.0f, 0.0f,
      0.0f, s.y,  0.0f,
      0.0f, 0.0f, s.z
   };
   return Matrix3x3(m);
}

Matrix3x3 Matrix3x3::createFromRotation (Coordtype angle, const Vector3& u) {

   Coordtype c = (Coordtype)Math::Cos(angle);
   Coordtype s = (Coordtype)Math::Sin(angle);
   Coordtype m[msNumElements] = {
	   u.x*u.x + (1.0f - u.x*u.x)*c, u.y*u.x*(1.0f - c) + u.z*s,   u.z*u.x*(1.0f - c) - u.y*s,
	   u.x*u.y*(1.0f - c) - u.z*s,   u.y*u.y + (1.0f - u.y*u.y)*c, u.z*u.y*(1.0f - c) + u.x*s,
	   u.x*u.z*(1.0f - c) + u.y*s,   u.y*u.z*(1.0f - c) - u.x*s,   u.z*u.z + (1.0f - u.z*u.z)*c
   };
   return Matrix3x3(m);
}

Matrix3x3 Matrix3x3::createFromBasis (const Vector3& u, const Vector3& v, const Vector3& w) {

	Coordtype m[msNumElements] = {
      u.x,  u.y,  u.z,
      v.x,  v.y,  v.z,
      w.x,  w.y,  w.z
   };
   return Matrix3x3(m);
}

