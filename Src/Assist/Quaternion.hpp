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
        Quaternion ();
        explicit Quaternion (Coordtype w, Coordtype x, Coordtype y, Coordtype z);
        explicit Quaternion (Coordtype w, const Vector3& vec);
        Quaternion (const Quaternion& other);
        virtual ~Quaternion ();

    // addition
        Quaternion&       sum (const Quaternion& q);
        static Quaternion sum (const Quaternion& q1, const Quaternion& q2);

    // subtraction
        Quaternion&       subtract (const Quaternion& q);
        static Quaternion subtract (const Quaternion& q1, const Quaternion& q2);

    // dot product
        Coordtype         dot (const Quaternion& q);
        static Coordtype  dot (const Quaternion& q1, const Quaternion& q2);

    // quaternion Hamilton product
        Quaternion&       multiply (const Quaternion& q);
        static Quaternion multiply (const Quaternion& q1, const Quaternion& q2);

    // multiply by scalar
        Quaternion&       scale (Coordtype r);
        static Quaternion scale (const Quaternion& q, Coordtype r);

    // divide by scalar
        Quaternion&       divide (Coordtype r);
        static Quaternion divide (const Quaternion& q, Coordtype r);

    // length
        Coordtype         length () const;
        static Coordtype  length (const Quaternion& q);

    // length squared
        Coordtype         lengthSquared () const;
        static Coordtype  lengthSquared (const Quaternion& q);

    // normalize
        Quaternion&       normalize ();
        Quaternion        normalized () const;
        static Quaternion normalized (const Quaternion& q);

    // conjugation
        Quaternion&       conjugate ();
        Quaternion        conjugate () const;
        static Quaternion conjugate (const Quaternion& q);

    // transform vector
        Vector3           transform(const Vector3& v) const;
        static Vector3    transform(const Quaternion& q, const Vector3& v);

    // inverse
        Quaternion&       invert ();
        Quaternion        inverse () const;
        static Quaternion inverse (const Quaternion& q);

    // operators overloaded
        Quaternion&       operator =  (const Quaternion& q);        // set
        bool              operator == (const Quaternion& q) const ; // equal
        bool              operator != (const Quaternion& q) const ; // not equal

        bool              operator <  (const Quaternion& q) const ; // for strict-weak ordering

        Quaternion        operator -  () const ;                    // unary minus

        Quaternion        operator +  (const Quaternion& q) const ; // sum
        Quaternion        operator -  (const Quaternion& q) const ; // subtract
		Quaternion        operator *  (const Quaternion& q) const;  // quaternion Hamilton product
		Vector3           operator *  (const Vector3& v) const;     // transform vector
        Quaternion        operator *  (Coordtype lambda) const ;    // multiply by scalar
        Quaternion        operator /  (Coordtype lambda) const ;    // divide by scalar

        Quaternion&       operator += (const Quaternion& q);        // "increase"
        Quaternion&       operator -= (const Quaternion& q);        // "decrease"
        Quaternion&       operator *= (Coordtype lambda);           // "multiply by scalar"
        Quaternion&       operator /= (Coordtype lambda);           // "divide by scalar"

        Coordtype         operator [] (int i) const;                // index
        Coordtype&        operator [] (int i);                      // index

                          operator const Coordtype* () const;       // cast to coordtype pointer

    // getters, setters
        Coordtype         getAngle () const;
        Vector3           getAxis () const;
        void              setAngle (Coordtype r);
        void              setAxis (const Vector3& v);

        Matrix3x3         toMatrix3x3 () const;
        Matrix4x4         toMatrix4x4 () const;

        static Quaternion createFromAxisAngle(Coordtype angle, const Vector3& axis);
		static Quaternion createFromAxes(const Vector3& x, const Vector3& y, const Vector3& z);

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
