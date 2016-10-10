/* ------------------------------------------------ *
*  Written by:      Nagy Balint                    *
*  Contact:         b.nagy.balint@gmail.com        *
*                                                  *
*  This file can be used/improved/redistributed    *
*  under GNU public license                        *
*                                                  *
*  Nagy Balint (C) 2015                            *
* ------------------------------------------------ */

#ifndef PLANE_HPP_
#define PLANE_HPP_

#include "Assist/Common.h"
#include "Assist/MathCommon.h"
#include "Assist/MatrixNxN.hpp"

// Represents a plane in 3-dimensional space.
//
// The plane consists of the (x,y,z) points satisfying the eqaution:
//    a*x + b*y + c*z + d = 0
//
// The side 

class Vector3;
class Matrix4x4;

class Plane
{
public:

	Plane();
	Plane(Coordtype a0, Coordtype b0, Coordtype c0, Coordtype d0);
	~Plane();

	Vector3 getNormal() const;
	Coordtype getSignedDistance() const;

	Plane&     operator =  (const Plane& other);
	bool       operator == (const Plane& other) const;
	bool       operator != (const Plane& other) const;

	Coordtype  operator [] (int i) const;
	Coordtype& operator [] (int i);

	// Create plane description using plane equation.
	// The plane is defined by the equation:
	//    a0*x + b0*y + c0*z + d0 = 0
	static Plane createFromEquation(Coordtype a0, Coordtype b0, Coordtype c0, Coordtype d0);
	static Plane createFromEquation(const Vector3& eqVec);

	// Create plane description using a point on the plane and the normal vector of the plane.
	// The normal should not be null-vector.
	static Plane createFromPointNormal(const Vector3& point, const Vector3& normal);

	// Create plane description using three points (a triangle). The points should span a plane, 
	// meaning that they do not all lie on a line.
	static Plane createFromTriangle(const Vector3& v0, const Vector3& v1, const Vector3& v2);

	// references to the components of the plane equation
	Coordtype& a;
	Coordtype& b;
	Coordtype& c;
	Coordtype& d;

	Coordtype p[4];
};

#endif /* PLANE_HPP_ */
