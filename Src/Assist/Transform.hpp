/* ------------------------------------------------ *
 *  Written by:      Nagy Balint                    *
 *  Contact:         b.nagy.balint@gmail.com        *
 *                                                  *
 *  This file can be used/improved/redistributed    *
 *  under GNU public license                        *
 *                                                  *
 *  Nagy Balint (C) 2010                            *
 * ------------------------------------------------ */

#ifndef TRANSFROM_HPP_
#define TRANSFROM_HPP_

#include "Assist/Common.h"
#include "Assist/MathCommon.h"
#include "Assist/Vector3.hpp"
#include "Assist/Quaternion.hpp"

class Transform {

    public:

        /// Constructor.
        Transform ();
        /// Constructor. Creates a transform using orientation matrix and translation vector)
        Transform (const Vector3& pos, const Quaternion& ori);

        /// Invert this transform.
        Transform& inverse ();
        /// Get the inverse of transform.
        static Transform inverse (const Transform& transform);

        /// Transform vector.
        Vector3 transform (const Vector3& u) const;

		Matrix4x4 toMatrix4x4() const;

        /// Getters
		const Vector3& getPosition() const;
		const Quaternion& getOrientation() const;

        /// Setters
		void setPosition(const Vector3& pos);
		void setOrientation(const Quaternion& ori);

        /// Identity transform.
        static Transform IDENTITY;

    protected:

        /// Basis of this transform.
        Quaternion mOrientation;

        /// Origin of this transformation. In other words: the translation applied
        /// to the point after the transformation by mOrientation
        Vector3 mPosition;

}; /* class Transform */

//----------------------------------------------------------------------------

inline const Quaternion& Transform::getOrientation () const {
    return mOrientation;
}

inline const Vector3& Transform::getPosition () const {
    return mPosition;
}

inline void Transform::setOrientation (const Quaternion& ori) {
    mOrientation = ori;
}

inline void Transform::setPosition (const Vector3& pos) {
    mPosition = pos;
}

#endif /* TRANSFROM_HPP_ */
