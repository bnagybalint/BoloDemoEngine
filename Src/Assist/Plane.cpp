#include "Plane.hpp"

#include "Assist/Vector3.hpp"

Plane::Plane()
	: a(p[0]), b(p[1]), c(p[2]), d(p[3])
{
	// for debugging purposes, set all values to sNAN
#ifdef BDE_GLOBAL_BUILD_DEBUG
	a = Math::B_NAN;
	b = Math::B_NAN;
	c = Math::B_NAN;
	d = Math::B_NAN;
#endif
}

Plane::Plane(Coordtype a0, Coordtype b0, Coordtype c0, Coordtype d0)
	: a(p[0]), b(p[1]), c(p[2]), d(p[3])
{
	Assert(a0 != 0.0f && b0 != 0.0f && c0 != 0.0f); // invalid plane equation

	a = a0;
	b = b0;
	c = c0;
	d = d0;
}

Plane::~Plane()
{
}

Vector3 Plane::getNormal() const
{
	return Vector3(a, b, c);
}

Coordtype Plane::getSignedDistance() const
{
	return d;
}

Plane& Plane::operator =  (const Plane& other)
{
	a = other.a;
	b = other.b;
	c = other.c;
	d = other.d;
	return *this;
}

bool Plane::operator == (const Plane& other) const
{
	return (a == other.a) && (b == other.b) && (c == other.c) && (d == other.d);

}

bool Plane::operator != (const Plane& other) const
{
	return (a != other.a) || (b != other.b) || (c != other.c) || (d != other.d);
}

Coordtype Plane::operator [] (int i) const {
	Assert(i >= 0 && i < 4);
	return p[i];
}

Coordtype& Plane::operator [] (int i) {
	Assert(i >= 0 && i < 4);
	return p[i];
}

/*static*/Plane createFromEquation(Coordtype a0, Coordtype b0, Coordtype c0, Coordtype d0)
{
	return Plane(a0, b0, c0, d0);
}

/*static*/Plane createFromEquation(const Vector3& eqVec)
{
	return Plane(eqVec.x, eqVec.y, eqVec.z, eqVec.w);
}


/*static*/Plane createFromPointNormal(const Vector3& point, const Vector3& normal)
{
	Assert(normal.lengthSquared() >= Coordtype_GeneralEpsSquared);

	Coordtype d0 = point.dot(normal);
	return Plane(normal.x, normal.y, normal.z, d0);
}


/*static*/Plane createFromTriangle(const Vector3& v0, const Vector3& v1, const Vector3& v2)
{
	Vector3 n = (v1 - v0) % (v2 - v0);
	Assert(n.lengthSquared() >= Coordtype_GeneralEpsSquared);
	return Plane::createFromPointNormal(v0, n.getNormalized());
}

