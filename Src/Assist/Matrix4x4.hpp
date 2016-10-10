/* ------------------------------------------------ *
 *  Written by:      Nagy Balint                    *
 *  Contact:         b.nagy.balint@gmail.com        *
 *                                                  *
 *  This file can be used/improved/redistributed    *
 *  under GNU public license                        *
 *                                                  *
 *  Nagy Balint (C) 2015                            *
 * ------------------------------------------------ */

#ifndef MATRIX4X4_HPP_
#define MATRIX4X4_HPP_

#include "Assist/Common.h"
#include "Assist/MathCommon.h"
#include "Assist/MatrixNxN.hpp"

// Represents a matrix of 4x4 floats.
//
// Logical layout of the matrix:
// 
//    [ m00 m01 m02 m03 ]
//    [ m10 m11 m12 m13 ]
//    [ m20 m21 m22 m23 ]
//    [ m30 m31 m32 m33 ]
// 
// Usage:
// 
//   Usage of this class conforms to the use of matrices in most mathematical 
//   papers. This was a design decision that has the benefit of understandability.
//	 
//   - Vectors passed (e.g. for matrix-vector multiplication) are interpreted as
//     column vectors. This means that vectors are left-multiplied by the matrix:
//                 [ m00, m01, m02, m03 ]   [ vx ]   [ m00*vx + m01*vy + m02*vz + m03*vw ]
//        M1 * v = [ m10, m11, m12, m13 ] * [ vy ] = [ m10*vx + m11*vy + m12*vz + m13*vw ] 
//                 [ m20, m21, m22, m23 ]   [ vz ]   [ m20*vx + m21*vy + m22*vz + m23*vw ]
//                 [ m30, m31, m32, m33 ]   [ vw ]   [ m20*vx + m21*vy + m22*vz + m23*vw ]
//
//   - Matrix multiplication is applied in the order it is written (matrix on the
//     left side is left-multiplies to the matrix on the right side):
//                [ f00, f01, f02, f03 ]   [ g00, g01, g02, g03 ]   [ f00*g00 + f01*g10 + f02*g20 + f03*g30, ... ]
//        F * G = [ f10, f11, f12, f13 ] * [ g10, g11, g12, g13 ] = [ f10*g00 + f11*g10 + f12*g20 + f13*g30, ... ]
//                [ f20, f21, f22, f23 ]   [ g20, g21, g22, g23 ]   [ f20*g00 + f21*g10 + f22*g20 + f23*g30, ... ]
//                [ f30, f31, f32, f33 ]   [ g30, g31, g32, g33 ]   [ f30*g00 + f31*g10 + f32*g20 + f33*g30, ... ]
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
//       [ m00, m10, m20, m30 ]
//       [ m01, m11, m21, m31 ]
//       [ m02, m12, m22, m32 ]
//       [ m03, m13, m23, m33 ]
//    or in flat view:
//       [ m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33 ]
//    This has the disadvantage that some interface methods are not trivial and 
//    they differ from the notation above. These methods are marked with a warning 
//    and should be used carefully.
//

class Vector3;
class Matrix3x3;
class Quaternion;

class Matrix4x4 : public MatrixNxN < 4 >
{
public:

    // constructors, destructor
	Matrix4x4();
	explicit Matrix4x4(Coordtype fill);
	explicit Matrix4x4(const Coordtype* m); // WARNING read doc before using this method
	Matrix4x4(Coordtype m00, Coordtype m01, Coordtype m02, Coordtype m03, Coordtype m10, Coordtype m11, Coordtype m12, Coordtype m13, Coordtype m20, Coordtype m21, Coordtype m22, Coordtype m23, Coordtype m30, Coordtype m31, Coordtype m32, Coordtype m33);
	Matrix4x4(const MatrixNxN<4>& m); // implicit conversion from parent class
	explicit Matrix4x4(const Matrix3x3& m);
	Matrix4x4(const Matrix4x4& m);
	virtual ~Matrix4x4();

    // ####################################

	// transform vector
	Vector3           transform(const Vector3& u) const;
	// transform vector by transpose of this matrix
	Vector3           transformByTranspose(const Vector3& u) const;
	// inverse
	// note: matrix should be invertible (detA != 0)
	Matrix4x4         inverse() const;
	// transpose
	Matrix4x4         transpose() const;
	// determinant
	Coordtype         determinant () const;
	// adjugate matrix
	Matrix4x4         adjugate() const;

	// ####################################

	// create matrix from rotation-scale, translation, projection and scalar parts
	//    [       |   ]
	//    [   R   | T ]
	//    [       |   ]
	//    [-------+---]
	//    [   P   | S ]
	Matrix4x4&        makeFromParts(const Matrix3x3& rotationPart, const Vector3& translationPart, const Vector3& projectionPart, Coordtype scalarPart);

	// create affine transformation matrix from translation, rotation and scale parts
	Matrix4x4&        makeAffineTransform(const Vector3& position, const Quaternion& orientation, const Vector3& scale);

	// ####################################

	// get row/column as a Vector3
	Vector3           getRow(unsigned int row) const;
	Vector3           getColumn(unsigned int column) const;

    // ####################################

    // operators overloaded
    Vector3           operator *  (const Vector3& u) const;   // right multiply by column vector

	// ####################################

	// create 3D scale matrix with given scaling factors
	static Matrix4x4  createScale(const Vector3& s);

	// create 3D rotation matrix for rotation by angle (in rads) around axis
	// note: axis should not be null vector
	static Matrix4x4  createRotationAxisAngle(Coordtype angle, const Vector3& u);

	// create 3D transformation matrix, which transforms standard (i,j,k)
	// base vectors into the given 3 vectors respectively
	// note: i,j,k must not be perpendicular to each other,
	//       but should not lie on a plane
	// note: neither of i,j,k should be null vector
	static Matrix4x4  createFromBasis(const Vector3& u, const Vector3& v, const Vector3& w);

	// create 3D translation matrix with given offsets
	static Matrix4x4  createTranslationMatrix(const Vector3& u);

	// create affine transformation matrix
	static Matrix4x4  createAffineTransform(const Vector3& position, const Quaternion& orientation, const Vector3& scale);

	// create matrix from rotation-scale, translation, projection and scalar parts
	//    [       |   ]
	//    [   R   | T ]
	//    [       |   ]
	//    [-------+---]
	//    [   P   | S ]
	static Matrix4x4  createFromParts(const Matrix3x3& rotationPart, const Vector3& translationPart, const Vector3& projectionPart, Coordtype scalarPart);

	// create matrix for symmetric projection transformation
	// 
	// fovY:   vertical view angle (in radians) 
	// aspect: aspect ratio (width/height) of the frustum
	// zNear:  z distance of the near plane
	// zFar:   z distance of the far plane
	// apexX:  relative horizontal position of the apex of the frustum [-1,1]
	// apexY:  relative vertical position of the apex of the frustum [-1,1]
	//
	// Apex placement: useful for creating asymmetrical frustums 
	//    (0,0) means the frustum is symmetrical
	//    (1,0) means the apex of the frustum is located "above" the right border of the near rectangle
	//    (0,1) means the apex of the frustum is located "above" the top border of the near rectangle
	static Matrix4x4  createProjection(Coordtype fovY, Coordtype aspect, Coordtype zNear, Coordtype zFar);
	static Matrix4x4  createProjectionAsymmetric(Coordtype fovY, Coordtype aspect, Coordtype zNear, Coordtype zFar, Coordtype apexX, Coordtype apexY);


    // special matrices
    static const Matrix4x4 IDENTITY;
    static const Matrix4x4 ZERO;

}; /* class Matrix4x4 */

#endif /* MATRIX4X4_HPP_ */
