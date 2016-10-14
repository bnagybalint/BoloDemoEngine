/* ------------------------------------------------ *
 *  Written by:      Nagy Balint                    *
 *  Contact:         b.nagy.balint@gmail.com        *
 *                                                  *
 *  This file can be used/improved/redistributed    *
 *  under GNU public license                        *
 *                                                  *
 *  Nagy Balint (C) 2015                            *
 * ------------------------------------------------ */

#include "Matrix4x4.hpp"

#include "Assist/Memory.h"
#include "Assist/Vector3.hpp"
#include "Assist/Quaternion.hpp"
#include "Assist/Matrix3x3.hpp"

// ############################################
// special matrices

const Matrix4x4 Matrix4x4::IDENTITY = Matrix4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
const Matrix4x4 Matrix4x4::ZERO = Matrix4x4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

// ############################################
// constructors, destructor

Matrix4x4::Matrix4x4 () {

	// for debugging purposes, set all values to sNAN
#ifdef BDE_GLOBAL_BUILD_DEBUG 
	for (unsigned int i = 0; i < msNumElements; ++i)
		mx[i] = Math::B_NAN;
#endif
}

Matrix4x4::Matrix4x4 (Coordtype fill) {

	for (unsigned int i = 0; i < msNumElements; ++i)
		mx[i] = fill;
}

Matrix4x4::Matrix4x4 (const Coordtype* m) {

	Memory::Memcopy(mx, m, msNumElements * sizeof(Coordtype));
}

Matrix4x4::Matrix4x4(
	Coordtype m00, Coordtype m01, Coordtype m02, Coordtype m03, 
	Coordtype m10, Coordtype m11, Coordtype m12, Coordtype m13, 
	Coordtype m20, Coordtype m21, Coordtype m22, Coordtype m23, 
	Coordtype m30, Coordtype m31, Coordtype m32, Coordtype m33)
{
	mx[mxidx(0, 0)] = m00;
	mx[mxidx(0, 1)] = m01;
	mx[mxidx(0, 2)] = m02;
	mx[mxidx(0, 3)] = m03;
	mx[mxidx(1, 0)] = m10;
	mx[mxidx(1, 1)] = m11;
	mx[mxidx(1, 2)] = m12;
	mx[mxidx(1, 3)] = m13;
	mx[mxidx(2, 0)] = m20;
	mx[mxidx(2, 1)] = m21;
	mx[mxidx(2, 2)] = m22;
	mx[mxidx(2, 3)] = m23;
	mx[mxidx(3, 0)] = m30;
	mx[mxidx(3, 1)] = m31;
	mx[mxidx(3, 2)] = m32;
	mx[mxidx(3, 3)] = m33;
}

Matrix4x4::Matrix4x4(const MatrixNxN<4>& m)
{
	Memory::Memcopy(mx, m.getData(), msNumElements * sizeof(Coordtype));
}

Matrix4x4::Matrix4x4(const Matrix3x3& m) {
	mx[mxidx(0, 0)] = m(0, 0);
	mx[mxidx(0, 1)] = m(0, 1);
	mx[mxidx(0, 2)] = m(0, 2);
	mx[mxidx(0, 3)] = Coordtype(0);

	mx[mxidx(1, 0)] = m(1, 0);
	mx[mxidx(1, 1)] = m(1, 1);
	mx[mxidx(1, 2)] = m(1, 2);
	mx[mxidx(1, 3)] = Coordtype(0);

	mx[mxidx(2, 0)] = m(2, 0);
	mx[mxidx(2, 1)] = m(2, 1);
	mx[mxidx(2, 2)] = m(2, 2);
	mx[mxidx(2, 3)] = Coordtype(0);

	mx[mxidx(3, 0)] = Coordtype(0);
	mx[mxidx(3, 1)] = Coordtype(0);
	mx[mxidx(3, 2)] = Coordtype(0);
	mx[mxidx(3, 3)] = Coordtype(1);
}

Matrix4x4::Matrix4x4 (const Matrix4x4& m) {
	Memory::Memcopy(mx, m.mx, msNumElements * sizeof(Coordtype));
}

Matrix4x4::~Matrix4x4 () { }

Vector3 Matrix4x4::transform(const Vector3& u) const {
	Coordtype rx = u.x*mx[mxidx(0, 0)] + u.y*mx[mxidx(0, 1)] + u.z*mx[mxidx(0, 2)] + u.w*mx[mxidx(0, 3)];
	Coordtype ry = u.x*mx[mxidx(1, 0)] + u.y*mx[mxidx(1, 1)] + u.z*mx[mxidx(1, 2)] + u.w*mx[mxidx(1, 3)];
	Coordtype rz = u.x*mx[mxidx(2, 0)] + u.y*mx[mxidx(2, 1)] + u.z*mx[mxidx(2, 2)] + u.w*mx[mxidx(2, 3)];
	Coordtype rw = u.x*mx[mxidx(3, 0)] + u.y*mx[mxidx(3, 1)] + u.z*mx[mxidx(3, 2)] + u.w*mx[mxidx(3, 3)];
	return Vector3(rx, ry, rz, rw);
}

Vector3 Matrix4x4::transformByTranspose(const Vector3& u) const {
	Coordtype rx = u.x*mx[mxidx(0, 0)] + u.y*mx[mxidx(1, 0)] + u.z*mx[mxidx(2, 0)] + u.w*mx[mxidx(3, 0)];
	Coordtype ry = u.x*mx[mxidx(0, 1)] + u.y*mx[mxidx(1, 1)] + u.z*mx[mxidx(2, 1)] + u.w*mx[mxidx(3, 1)];
	Coordtype rz = u.x*mx[mxidx(0, 2)] + u.y*mx[mxidx(1, 2)] + u.z*mx[mxidx(2, 2)] + u.w*mx[mxidx(3, 2)];
	Coordtype rw = u.x*mx[mxidx(0, 3)] + u.y*mx[mxidx(1, 3)] + u.z*mx[mxidx(2, 3)] + u.w*mx[mxidx(3, 3)];
	return Vector3(rx, ry, rz, rw);
}

Matrix4x4 Matrix4x4::inverse () const {
	Coordtype d = determinant();
	Assert(d != 0.0f);

	return adjugate() / d;
}

// ############################################
// transpose

Matrix4x4 Matrix4x4::transpose () const {
	Matrix4x4 r;
	for (int i = 0; i < msNumRows; i++) {
		for (int j = 0; j < msNumCols; j++) {
			r.mx[mxidx(i,j)] = mx[mxidx(j,i)];
		}
	}
   return r;
}

// ############################################
// determinant

#define a11 (this->mx[mxidx(0,0)])
#define a12 (this->mx[mxidx(0,1)])
#define a13 (this->mx[mxidx(0,2)])
#define a14 (this->mx[mxidx(0,3)])
#define a21 (this->mx[mxidx(1,0)])
#define a22 (this->mx[mxidx(1,1)])
#define a23 (this->mx[mxidx(1,2)])
#define a24 (this->mx[mxidx(1,3)])
#define a31 (this->mx[mxidx(2,0)])
#define a32 (this->mx[mxidx(2,1)])
#define a33 (this->mx[mxidx(2,2)])
#define a34 (this->mx[mxidx(2,3)])
#define a41 (this->mx[mxidx(3,0)])
#define a42 (this->mx[mxidx(3,1)])
#define a43 (this->mx[mxidx(3,2)])
#define a44 (this->mx[mxidx(3,3)])

Coordtype Matrix4x4::determinant () const {

	Coordtype det = 0;
	det += a11*( a22*a33*a44 + a23*a34*a42 + a24*a32*a43 - a24*a33*a42 - a34*a43*a22 - a44*a23*a32 );
	det -= a12*( a21*a33*a44 + a23*a34*a41 + a24*a31*a43 - a24*a33*a41 - a34*a43*a21 - a44*a23*a31 );
	det += a13*( a21*a32*a44 + a22*a34*a41 + a24*a31*a42 - a24*a32*a41 - a34*a42*a21 - a44*a22*a31 );
	det -= a14*( a21*a32*a43 + a22*a33*a41 + a23*a31*a42 - a23*a32*a41 - a33*a42*a21 - a43*a22*a31 );
	return det;
}

// ############################################
// adjugate matrix

#define b11 (a22*a33*a44 + a23*a34*a42 + a24*a32*a43 - a22*a34*a43 - a23*a32*a44 - a24*a33*a42)
#define b12 (a21*a33*a44 + a23*a34*a41 + a24*a31*a43 - a21*a34*a43 - a23*a31*a44 - a24*a33*a41)
#define b13 (a21*a32*a44 + a22*a34*a41 + a24*a31*a42 - a21*a34*a42 - a22*a31*a44 - a24*a32*a41)
#define b14 (a21*a32*a43 + a22*a33*a41 + a23*a31*a42 - a21*a33*a42 - a22*a31*a43 - a23*a32*a41)

#define b21	(a12*a33*a44 + a13*a34*a42 + a14*a32*a43 - a12*a34*a43 - a13*a32*a44 - a14*a33*a42)
#define b22	(a11*a33*a44 + a13*a34*a41 + a14*a31*a43 - a11*a34*a43 - a13*a31*a44 - a14*a33*a41)
#define b23	(a11*a32*a44 + a12*a34*a41 + a14*a31*a42 - a11*a34*a42 - a12*a31*a44 - a14*a32*a41)
#define b24	(a11*a32*a43 + a12*a33*a41 + a13*a31*a42 - a11*a33*a42 - a12*a31*a43 - a13*a32*a41)

#define b31	(a12*a23*a44 + a13*a24*a42 + a14*a22*a43 - a12*a24*a43 - a13*a22*a44 - a14*a23*a42)
#define b32	(a11*a23*a44 + a13*a24*a41 + a14*a21*a43 - a11*a24*a43 - a13*a21*a44 - a14*a23*a41)
#define b33	(a11*a22*a44 + a12*a24*a41 + a14*a21*a42 - a11*a24*a42 - a12*a21*a44 - a14*a22*a41)
#define b34	(a11*a22*a43 + a12*a23*a41 + a13*a21*a42 - a11*a23*a42 - a12*a21*a43 - a13*a22*a41)

#define b41	(a12*a23*a34 + a13*a24*a32 + a14*a22*a33 - a12*a24*a33 - a13*a22*a34 - a14*a23*a32)
#define b42	(a11*a23*a34 + a13*a24*a31 + a14*a21*a33 - a11*a24*a33 - a13*a21*a34 - a14*a23*a31)
#define b43	(a11*a22*a34 + a12*a24*a31 + a14*a21*a32 - a11*a24*a32 - a12*a21*a34 - a14*a22*a31)
#define b44	(a11*a22*a33 + a12*a23*a31 + a13*a21*a32 - a11*a23*a32 - a12*a21*a33 - a13*a22*a31)

Matrix4x4 Matrix4x4::adjugate () const {

	return Matrix4x4(
		b11, -b12, b13, -b14,
		-b21, b22, -b23, b24,
		b31, -b32, b33, -b34,
		-b41, b42, -b43, b44
		);
}

#undef 	a11
#undef 	a12
#undef 	a13
#undef 	a14
#undef 	a21
#undef 	a22
#undef 	a23
#undef 	a24
#undef 	a31
#undef 	a32
#undef 	a33
#undef 	a34
#undef 	a41
#undef 	a42
#undef 	a43
#undef 	a44

#undef 	b11
#undef 	b12
#undef 	b13
#undef 	b14
#undef 	b21
#undef 	b22
#undef 	b23
#undef 	b24
#undef 	b31
#undef 	b32
#undef 	b33
#undef 	b34
#undef 	b41
#undef 	b42
#undef 	b43
#undef 	b44

Matrix4x4& Matrix4x4::makeFromParts(const Matrix3x3& rotationPart, const Vector3& translationPart, const Vector3& projectionPart, Coordtype scalarPart) {
	mx[mxidx(0, 0)] = rotationPart(0, 0);
	mx[mxidx(0, 1)] = rotationPart(0, 1);
	mx[mxidx(0, 2)] = rotationPart(0, 2);
	mx[mxidx(0, 3)] = translationPart.x;

	mx[mxidx(1, 0)] = rotationPart(1, 0);
	mx[mxidx(1, 1)] = rotationPart(1, 1);
	mx[mxidx(1, 2)] = rotationPart(1, 2);
	mx[mxidx(1, 3)] = translationPart.y;

	mx[mxidx(2, 0)] = rotationPart(2, 0);
	mx[mxidx(2, 1)] = rotationPart(2, 1);
	mx[mxidx(2, 2)] = rotationPart(2, 2);
	mx[mxidx(2, 3)] = translationPart.z;

	mx[mxidx(3, 0)] = projectionPart.x;
	mx[mxidx(3, 1)] = projectionPart.y;
	mx[mxidx(3, 2)] = projectionPart.z;
	mx[mxidx(3, 3)] = scalarPart;

	return *this;
}

Matrix4x4& Matrix4x4::makeAffineTransform(const Vector3& position, const Quaternion& orientation, const Vector3& scale) {
	makeFromParts(orientation.toMatrix3x3() * Matrix3x3::createScale(scale), position, Vector3::ZERO, Coordtype(1));
	return *this;
}

// get row/column as a Vector3
Vector3 Matrix4x4::getRow(unsigned int row) const
{
	Assert(row >= 0 && row <= msNumRows - 1);
	return Vector3(mx[mxidx(row, 0)], mx[mxidx(row, 1)], mx[mxidx(row, 2)], mx[mxidx(row, 3)]);
}
Vector3 Matrix4x4::getColumn(unsigned int col) const {
	Assert(col >= 0 && col <= msNumCols - 1);
	return Vector3(mx[mxidx(0, col)], mx[mxidx(1, col)], mx[mxidx(2, col)], mx[mxidx(3, col)]);
}

Vector3 Matrix4x4::operator *  (const Vector3& u) const {
	return transform(u);
}

Matrix4x4 Matrix4x4::createScale(const Vector3& s) {
	Matrix4x4 rv;
	rv.makeFromParts(Matrix3x3::createScale(s), Vector3::ZERO, Vector3::ZERO, Coordtype(1));
	return rv;
}

Matrix4x4 Matrix4x4::createRotationAxisAngle(Coordtype angle, const Vector3& u) {
	Matrix4x4 rv;
	rv.makeFromParts(Matrix3x3::createRotationAxisAngle(angle, u), Vector3::ZERO, Vector3::ZERO, Coordtype(1));
	return rv;
}

Matrix4x4 Matrix4x4::createFromBasis(const Vector3& u, const Vector3& v, const Vector3& w) {
	Matrix4x4 rv;
	rv.makeFromParts(Matrix3x3::createFromBasis(u, v, w), Vector3::ZERO, Vector3::ZERO, Coordtype(1));
	return rv;
}

Matrix4x4 Matrix4x4::createTranslationMatrix(const Vector3& u) {
	Matrix4x4 rv;
	rv.makeFromParts(Matrix3x3::IDENTITY, u, Vector3::ZERO, Coordtype(1));
	return rv;
}

Matrix4x4 Matrix4x4::createAffineTransform(const Vector3& position, const Quaternion& orientation, const Vector3& scale)
{
	Matrix4x4 rv;
	rv.makeFromParts(orientation.toMatrix3x3() * Matrix3x3::createScale(scale), position, Vector3::ZERO, Coordtype(1));
	return rv;
}

Matrix4x4 Matrix4x4::createFromParts(const Matrix3x3& rotationPart, const Vector3& translationPart, const Vector3& projectionPart, Coordtype scalarPart)
{
	Matrix4x4 rv;
	rv.makeFromParts(rotationPart, translationPart, projectionPart, scalarPart);
	return rv;
}

Matrix4x4 Matrix4x4::createProjection(Coordtype fovY, Coordtype aspect, Coordtype zNear, Coordtype zFar)
{
	Assert(fovY > 0.0f && aspect < Math::B_PI);
	Assert(aspect > 0.0f);
	Assert(zNear > 0.0f);
	Assert(zFar > 0.0f);
	Assert(zFar > zNear);

	// In symmetric case:
	//   l = -r
	//   b = -t
	// 
	// Symmetric projection matrix:
	//
	//   [ Zn/r  0     0                 0                   ]
	//   [ 0     Zn/t  0                 0                   ]
	//   [ 0     0     (-Zf-Zn)/(Zf-Zn)  (-2*Zf*Zn)/(Zf-Zn)  ]
	//   [ 0     0     -1                0                   ]

	Coordtype t = Math::Tan(0.5f * fovY) * zNear;
	Coordtype r = t * aspect;
	Coordtype A = zNear / r;
	Coordtype B = zNear / t;
	Coordtype C = -(zFar + zNear) / (zFar - zNear);
	Coordtype D = -(2.0f * zFar * zNear) / (zFar - zNear);
	Coordtype E = -1.0f;

// 	Coordtype t = Math::Tan(0.5f * fovY) * zNear;
// 	Coordtype r = t * aspect;
// 	Coordtype Q = zFar / (zFar - zNear);
// 	Coordtype A = zNear / r;
// 	Coordtype B = zNear / t;
// 	Coordtype C = Q;
// 	Coordtype D = -Q * zNear;
// 	Coordtype E = 1.0f;

	return Matrix4x4(
		A, 0, 0, 0,
		0, B, 0, 0,
		0, 0, C, D,
		0, 0, E, 0
		);
}

Matrix4x4 Matrix4x4::createProjectionAsymmetric(Coordtype fovY, Coordtype aspect, Coordtype zNear, Coordtype zFar, Coordtype apexX, Coordtype apexY)
{
	Untested();

	Assert(fovY > 0.0f && aspect < Math::B_PI);
	Assert(aspect > 0.0f);
	Assert(zNear > 0.0f);
	Assert(zFar > 0.0f);
	Assert(zFar > zNear);

	// General projection matrix:
	//
	//   [ 2*Zn/(r-l)  0           (r+l)/(r-l)       0                   ]
	//   [ 0           2*Zn/(t-b)  (t+b)/(t-b)       0                   ]
	//   [ 0           0           (-Zf-Zn)/(Zf-Zn)  (-2*Zf*Zn)/(Zf-Zn)  ]
	//   [ 0           0           -1                0                   ]

	Coordtype ey = Math::Tan(0.5f * fovY) * zNear;
	Coordtype ex = ey / aspect;

	Coordtype l = -(1.0f + apexX) * ex;
	Coordtype r = (1.0f - apexX) * ex;
	Coordtype b = -(1.0f + apexY) * ey;
	Coordtype t = (1.0f - apexY) * ey;

	Coordtype A = (2.0f * zNear) / (r - l);
	Coordtype B = (2.0f * zNear) / (t - b);
	Coordtype C = -(zFar + zNear) / (zFar - zNear);
	Coordtype D = -(2.0f * zFar * zNear) / (zFar - zNear);
	Coordtype E = -1.0f;
	Coordtype F = (r + l) / (r - l);
	Coordtype G = (t + b) / (t - b);

	return Matrix4x4(
		A, 0, F, 0,
		0, B, G, 0,
		0, 0, C, D,
		0, 0, E, 0
		);
}
