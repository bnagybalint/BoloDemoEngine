/* ------------------------------------------------ *
 *  Written by:      Nagy Balint                    *
 *  Contact:         b.nagy.balint@gmail.com        *
 *                                                  *
 *  This file can be used/improved/redistributed    *
 *  under GNU public license                        *
 *                                                  *
 *  Nagy Balint (C) 2015                            *
 * ------------------------------------------------ */

#ifndef MATRIX3X3_HPP_
#define MATRIX3X3_HPP_

#include "Assist/Common.h"
#include "Assist/MathCommon.h"
#include "Assist/MatrixNxN.hpp"

// Represents a matrix of 3x3 floats.
//
// Logical layout of the matrix:
// 
//    [ m00 m01 m02 ]
//    [ m10 m11 m12 ]
//    [ m20 m21 m22 ]
// 
// Usage:
// 
//   Usage of this class conforms to the use of matrices in most mathematical 
//   papers. This was a design decision that has the benefit of understandability.
//	 
//   - Vectors passed (e.g. for matrix-vector multiplication) are interpreted as
//     column vectors. This means that vectors are left-multiplied by the matrix:
//                 [ m00, m01, m02 ]   [ vx ]   [ m00*vx + m01*vy + m02*vz ]
//        M1 * v = [ m10, m11, m12 ] * [ vy ] = [ m10*vx + m11*vy + m12*vz ]
//                 [ m20, m21, m22 ]   [ vz ]   [ m20*vx + m21*vy + m22*vz ]
//
//   - Matrix multiplication is applied in the order it is written (matrix on the
//     left side is left-multiplies to the matrix on the right side):
//                [ f00, f01, f02 ]   [ g00, g01, g02 ]   [ f00*g00 + f01*g10 + f02*g20 ]
//        F * G = [ f10, f11, f12 ] * [ g10, g11, g12 ] = [ f10*g00 + f11*g10 + f12*g20 ]
//                [ f20, f21, f22 ]   [ g20, g21, g22 ]   [ f20*g00 + f21*g10 + f22*g20 ]
//     In other words: the ij'th element of the resulting matrix will be the 
//     scalar product row i of the matrix on the left and column j of the matrix
//     on the right.
//
//   - Because of the following two properties, the following is true:
//        F * G * v = 
//        F * (G*v) =
//        (F*G) * v
//
//   - Also, we can interpret a matrix multiplication chain as follows
//     (right-to-left notation):
//        M1 * M2 * M3 * v0 = v3
//     if 
//        v1 := M3 * v0;
//        v2 := M2 * v1;
//        vr := M1 * v2;
//
// Remarks:
// 
//    When designing the class and its inner workings I wanted to create a memory 
//    layout, that can be directly passed/converted to DirectX (without the need 
//    for matrix transpose). For this reason, the memory layout looks like this:
//       [ m00, m10, m20 ]
//       [ m01, m11, m21 ]
//       [ m02, m12, m22 ]
//    or in flat view:
//       [ m00, m10, m20, m01, m11, m21, m02, m12, m22 ]
//    This has the disadvantage that some interface methods are not trivial and 
//    they differ from the notation above. These methods are marked with a warning 
//    and should be used carefully.
//

class Vector3;
class Matrix4x4;

class Matrix3x3 : public MatrixNxN < 3 >
{
public:

	// constructors, destructor
	Matrix3x3();
	explicit Matrix3x3(Coordtype fill);
	explicit Matrix3x3(const Coordtype* data); // WARNING read doc before using this method
	Matrix3x3(Coordtype m00, Coordtype m01, Coordtype m02, Coordtype m10, Coordtype m11, Coordtype m12, Coordtype m20, Coordtype m21, Coordtype m22);
	Matrix3x3(const MatrixNxN<3>& m); // implicit conversion from parent class
	Matrix3x3(const Matrix3x3& m);
	virtual ~Matrix3x3();

	// ####################################

	// transform vector
	Vector3           transform(const Vector3& u) const;
	// transform vector by transpose of this matrix
	Vector3           transformByTranspose(const Vector3& u) const;
	// inverse
	// note: matrix should be invertible (detA != 0)
	Matrix3x3         inverse() const;
	// transpose
	Matrix3x3         transpose() const;
	// determinant
	Coordtype         determinant() const;
	// adjugate matrix
	Matrix3x3         adjugate() const;
	// re-orthogonalize matrix
	Matrix3x3         orthogonalized() const;

	// ####################################

	Matrix4x4         toMatrix4x4() const;

	// get row/column as a Vector3
	Vector3           getRow(unsigned int row) const;
	Vector3           getColumn(unsigned int column) const;

	// ####################################

	// operators overloaded
	Vector3           operator *  (const Vector3& u) const;   // right multiply by column vector

	using MatrixNxN::operator = ;
	using MatrixNxN::operator ==;
	using MatrixNxN::operator !=;
	using MatrixNxN::operator + ;
	using MatrixNxN::operator - ;
	using MatrixNxN::operator * ;
	using MatrixNxN::operator / ;
	using MatrixNxN::operator +=;
	using MatrixNxN::operator -=;
	using MatrixNxN::operator *=;
	using MatrixNxN::operator /=;
	using MatrixNxN::operator ();

	// ####################################

	// create 3D scale matrix with given scaling factors
	static Matrix3x3  createScale(const Vector3& s);

	// create 3D rotation matrix for rotation by angle (in rads) around axis
	// note: axis should not be null vector
	static Matrix3x3  createRotationAxisAngle(Coordtype radians, const Vector3& u);

	// create 3D transformation matrix, which transforms standard (i,j,k)
	// base vectors into the given 3 vectors respectively
	// note: i,j,k must not be perpendicular to each other,
	//       but should not lie on a plane
	// note: neither of i,j,k should be null vector
	static Matrix3x3  createFromBasis(const Vector3& u, const Vector3& v, const Vector3& w);

	// special matrices
	static const Matrix3x3 IDENTITY;
	static const Matrix3x3 ZERO;

}; /* class Matrix3x3 */

#endif /* MATRIX3X3_HPP_ */
