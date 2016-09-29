/* ------------------------------------------------ *
 *  Written by:      Nagy Balint                    *
 *  Contact:         b.nagy.balint@gmail.com        *
 *                                                  *
 *  This file can be used/improved/redistributed    *
 *  under GNU public license                        *
 *                                                  *
 *  Nagy Balint (C) 2010                            *
 * ------------------------------------------------ */

#ifndef VECTOR3_HPP_
#define VECTOR3_HPP_

#include "Assist/Common.h"
#include "Assist/MathCommon.h"

// *****************************************************************
//  Class: Vector3
//
//  Represents an vector in 3-dimensional Euclidean space with
//  x,y,z coordinates. Some operations have static version along
//  with their non-static pairs. It is a general rule, that all
//  static methods return a temporal instance of the class, and
//  all non-static versions *will* modify the instance itself
//  (except for those methods, that do not modify the instance,
//  like dot product or angle-between). For example:
//
//    --> Vector3& sum(Vector3& W) sums w with the instance (v),
//        store it in v and return with a reference to v. In other
//        words, it does v := v+w.
//    --> static Vector3 sum(Vector3& v, Vector3& w) sums v
//        with w, stores it in a new local instance, then returns
//        with it. In other words, it does: return v+w.
//
//  For convinient coding, there are constants defined for
//  one and two vector argument functions. They are named VEX_XXX
//  for one vector argument and VEC_XXX_XXX for two vector arguments
//  where XXX can be either:
//    --> REF: a vector by reference (Vector3& v)
//    --> PTR: a vector by pointer (Vector3* v)
//    --> XYZ: a vector by specifying all three coordinates
//        (Coordtype x,y,z)
//
//  There are no definitions for mixed types, for example Coordtype x0, Coordtype y0, Coordtype z0_REF
//  is not defined.
//
// ****************************************************************

class Vector3 {

public:

	// constructors
	Vector3 ();
	explicit Vector3 (Coordtype xyz);
	Vector3 (const Vector3& u);
	Vector3 (Coordtype x0, Coordtype y0, Coordtype z0);
	Vector3 (Coordtype x0, Coordtype y0, Coordtype z0, Coordtype w0);
	virtual ~Vector3 ();

	// copy, clear and fill
	Vector3&          copy (const Vector3& u);
	Vector3&          clear();
	Vector3&          fill(Coordtype value);

	// ####################################

	// addition
	Vector3           sum (const Vector3& u) const;
	// subtraction
	Vector3           subtract (const Vector3& u) const;
	// dot product
	Coordtype         dot (const Vector3& u) const;
	// cross product
	Vector3           cross (const Vector3& u) const;
	// box product (a.k.a. scalar triple product)  ( = this . (v1 x v2) )
	Coordtype         box (const Vector3& u, const Vector3& v) const;
	// vector triple product   ( = (this x v1) x v2 )
	Vector3           triple (const Vector3& u, const Vector3& v) const;
	// coordinate-wise multiplication
	Vector3           coordWiseMultiply(const Vector3& u) const;

	// normalize
	Vector3&          normalize ();
	Vector3           getNormalized () const;

	// absolute - get vector with all negative values inverted
	Vector3           abs () const;
	// interpolate
	Vector3           interpolate (const Vector3& u, Coordtype t) const;
	// mix(v1,v2,a,b) -> a*v1 + b*v2
	Vector3           mix(const Vector3& u, Coordtype ta, Coordtype tb) const;
	// reflect
	Vector3           reflect (const Vector3& u) const;

	// project to plane defined by normal vector
	Vector3           project (const Vector3& u) const;

	// ####################################

	// length
	Coordtype         length () const;
	// length squared
	Coordtype         lengthSquared () const;

	// distance
	Coordtype         distance (const Vector3& u) const;
	// angle of two vectors
	Coordtype         angle (const Vector3& u) const;
	// signed angle of two vectors on plane
	// defined by its normal vector
	Coordtype         angleSigned (const Vector3& u, const Vector3& v) const;

	// get a random vector (equally distributed)
	// that has theta as an angle between it and this
	// TODO move to random
	Vector3           randomPerturbed (Coordtype theta) const;
	// get random vector equally distributed on the surface of the unit sphere
	// TODO move to random 
	static Vector3    randomUnit ();

	// ####################################

	// operators overloaded
	Vector3&          operator =  (const Vector3& u);        // set
	bool              operator == (const Vector3& u) const;  // equal
	bool              operator != (const Vector3& u) const;  // not equal

	bool              operator <  (const Vector3& u) const;  // for strict-weak ordering

	Vector3           operator -  () const ;                 // unary minus

	Vector3           operator +  (const Vector3& u) const;  // sum
	Vector3           operator -  (const Vector3& u) const;  // subtract
	Coordtype         operator *  (const Vector3& u) const;  // dot product
	Vector3           operator %  (const Vector3& u) const;  // cross product
	Vector3           operator *  (Coordtype lambda) const;  // multiply by scalar
	Vector3           operator /  (Coordtype lambda) const;  // divide by scalar

	Vector3&          operator += (const Vector3& u);        // "increase"
	Vector3&          operator -= (const Vector3& u);        // "decrease"
	Vector3&          operator *= (Coordtype lambda);        // "multiply by scalar"
	Vector3&          operator /= (Coordtype lambda);        // "divide by scalar"

	Coordtype         operator [] (int i) const;             // index
	Coordtype&        operator [] (int i);                   // index

	/**/              operator const Coordtype* () const;    // cast to coordtype pointer

	// ####################################

	// coordinates
	void              xyz (Coordtype* arr) const;

	// ####################################

	// special vectors
	static const Vector3 UNIT_X;
	static const Vector3 UNIT_Y;
	static const Vector3 UNIT_Z;
	static const Vector3 UNIT_NEG_X;
	static const Vector3 UNIT_NEG_Y;
	static const Vector3 UNIT_NEG_Z;
	static const Vector3 ZERO;
	static const Vector3 UNIT_SCALE;

	// references to the components of the vector
	Coordtype& x;
	Coordtype& y;
	Coordtype& z;
	Coordtype& w;

	// ####################################

	// x,y,z and w components of the vector
	Coordtype c[4];

	// friend functions
	friend Vector3 operator * (Coordtype lambda, const Vector3& u);

}; /* class Vector3 */

// outer functions
Vector3 operator * (Coordtype lambda, const Vector3& u); // multiply by scalar

typedef Vector3 Vector4;

#endif /* VECTOR3_HPP_ */
