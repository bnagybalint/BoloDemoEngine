/* ------------------------------------------------ *
 *  Written by:      Nagy Balint                    *
 *  Contact:         b.nagy.balint@gmail.com        *
 *                                                  *
 *  This file can be used/improved/redistributed    *
 *  under GNU public license                        *
 *                                                  *
 *  Nagy Balint (C) 2010                            *
 * ------------------------------------------------ */

#ifndef QUATERNION_HPP_
#define QUATERNION_HPP_

#include "Assist/Common.h"
#include "Assist/MathCommon.h"

class Vector3;
class Matrix4x4;
class Matrix3x3;

class Quaternion {

public:

	// constructors
	Quaternion();
	explicit Quaternion(Coordtype w, Coordtype x, Coordtype y, Coordtype z);
	explicit Quaternion(Coordtype w, const Vector3& vec);
	Quaternion(const Quaternion& other);
	virtual ~Quaternion();

	// addition
	Quaternion        sum(const Quaternion& q) const;
	// subtraction
	Quaternion        subtract(const Quaternion& q) const;
	// dot product
	Coordtype         dot(const Quaternion& q) const;
	// quaternion Hamilton product
	Quaternion        multiply(const Quaternion& q) const;
	// length
	Coordtype         length() const;
	// length squared
	Coordtype         lengthSquared() const;
	// normalize
	Quaternion        normalize() const;
	// conjugation
	Quaternion        conjugate() const;

	// transform vector
	Vector3           transform(const Vector3& v) const;

	// inverse
	Quaternion        inverse() const;

	// operators overloaded
	Quaternion&       operator =  (const Quaternion& q);        // set
	bool              operator == (const Quaternion& q) const; // equal
	bool              operator != (const Quaternion& q) const; // not equal

	bool              operator <  (const Quaternion& q) const; // for strict-weak ordering

	Quaternion        operator -  () const;                    // unary minus

	Quaternion        operator +  (const Quaternion& q) const; // sum
	Quaternion        operator -  (const Quaternion& q) const; // subtract
	Quaternion        operator *  (const Quaternion& q) const;  // quaternion Hamilton product
	Vector3           operator *  (const Vector3& v) const;     // transform vector
	Quaternion        operator *  (Coordtype lambda) const;    // multiply by scalar
	Quaternion        operator /  (Coordtype lambda) const;    // divide by scalar

	Quaternion&       operator += (const Quaternion& q);        // "increase"
	Quaternion&       operator -= (const Quaternion& q);        // "decrease"
	Quaternion&       operator *= (Coordtype lambda);           // "multiply by scalar"
	Quaternion&       operator /= (Coordtype lambda);           // "divide by scalar"

	Coordtype         operator [] (int i) const;                // index
	Coordtype&        operator [] (int i);                      // index

	operator const Coordtype* () const;       // cast to coordtype pointer

	// getters, setters
	Coordtype         getAngle() const;
	Vector3           getAxis() const;
	void              setAngle(Coordtype r);
	void              setAxis(const Vector3& v);

	Matrix3x3         toMatrix3x3() const;
	Matrix4x4         toMatrix4x4() const;

	static Quaternion createFromAxisAngle(Coordtype radians, const Vector3& axis);
	static Quaternion createFromBasis(const Vector3& x, const Vector3& y, const Vector3& z);

	static Quaternion IDENTITY;

	// references to the components
	Coordtype& w;
	Coordtype& x;
	Coordtype& y;
	Coordtype& z;

private:

	Coordtype q[4];

}; /* class Quaternion */

#endif /* QUATERNION_HPP_ */
