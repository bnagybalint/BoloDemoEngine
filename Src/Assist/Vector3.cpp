/* ------------------------------------------------ *
 *  Written by:      Nagy Balint                    *
 *  Contact:         b.nagy.balint@gmail.com        *
 *                                                  *
 *  This file can be used/improved/redistributed    *
 *  under GNU public license                        *
 *                                                  *
 *  Nagy Balint (C) 2010                            *
 * ------------------------------------------------ */

#include "Vector3.hpp"

#include "Assist/MathCommon.h"
#include "Assist/Random.h" // TODO this should not be needed

// ############################################
// constructors

Vector3::Vector3 ()
	:x(c[0]), y(c[1]), z(c[2]), w(c[3]) {

	// for debugging purposes, set all values to sNAN
#ifdef BDE_GLOBAL_BUILD_DEBUG
	x = Math::B_NAN;
	y = Math::B_NAN;
	z = Math::B_NAN;
	w = Math::B_NAN;
#endif
}

Vector3::Vector3 (Coordtype xyz)
	:x(c[0]), y(c[1]), z(c[2]), w(c[3]) {

	c[0] = c[1] = c[2] = xyz;
	c[3] = 0.0f;
}

Vector3::Vector3 (const Vector3& u)
	:x(c[0]), y(c[1]), z(c[2]), w(c[3]) {

	c[0] = u.x;
	c[1] = u.y;
	c[2] = u.z;
	c[3] = u.w;
}

Vector3::Vector3 (Coordtype x0, Coordtype y0, Coordtype z0)
	:x(c[0]), y(c[1]), z(c[2]), w(c[3]) {

	c[0] = x0;
	c[1] = y0;
	c[2] = z0;
	c[3] = 0.0f;
}

Vector3::Vector3 (Coordtype x0, Coordtype y0, Coordtype z0, Coordtype w0)
	:x(c[0]), y(c[1]), z(c[2]), w(c[3]) {

	c[0] = x0;
	c[1] = y0;
	c[2] = z0;
	c[3] = w0;
}

Vector3::~Vector3 () { }

// ############################################
// copy

Vector3& Vector3::copy (const Vector3& u) {

	x = u.x;
	y = u.y;
	z = u.z;
	w = u.w;
	return *this;
}

Vector3& Vector3::clear() {
	x = y = z = w = 0.0f;
	return *this;
}

Vector3& Vector3::fill(Coordtype value) {
	x = y = z = w = value;
	return *this;
}

Vector3 Vector3::sum(const Vector3& u) const {
	return Vector3(x + u.x, y + u.y, z + u.z);
}

Vector3 Vector3::subtract(const Vector3& u) const {
	return Vector3(x - u.x, y - u.y, z - u.z);
}

Coordtype Vector3::dot(const Vector3& u) const {
	return x*u.x + y*u.y + z*u.z;
}

Vector3 Vector3::cross(const Vector3& u) const {
	return Vector3(y*u.z - z*u.y, 
	/**/           z*u.x - x*u.z,
	/**/           x*u.y - y*u.x);
}

Coordtype Vector3::box (const Vector3& u, const Vector3& v) const {

	return x*(u.y*v.z - u.z*v.y) -
	/**/   y*(u.x*v.z - u.z*v.x) +
	/**/   z*(u.x*v.y - u.y*v.x);
}

Vector3 Vector3::triple (const Vector3& u, const Vector3& v) const {
	return mix(u, -v.dot(u), v.dot(*this));
}

Vector3 Vector3::coordWiseMultiply(const Vector3& u) const {
	return Vector3(x*u.x, y*u.y, z*u.z, w*u.w);
}

Vector3& Vector3::normalize () {

	Coordtype l = length();
	x /= l;
	y /= l;
	z /= l;
	return *this;
}

Vector3 Vector3::getNormalized () const {

	Coordtype l = length();
	return Vector3(x / l, y / l, z / l);
}

Vector3 Vector3::abs () const {
	x = Math::Abs(x);
	y = Math::Abs(y);
	z = Math::Abs(z);
	return *this;
}

Vector3 Vector3::interpolate (const Vector3& u, Coordtype t) const {
	return Vector3((1.0f - t)*x + t*u.x,
	/**/           (1.0f - t)*y + t*u.y,
	/**/           (1.0f - t)*z + t*u.z);
}

Vector3 Vector3::mix (const Vector3& u, Coordtype ta, Coordtype tb) const {
	return Vector3(ta*x + tb*u.x,
	/**/           ta*y + tb*u.y,
	/**/           ta*z + tb*u.z);
}

Vector3 Vector3::reflect (const Vector3& u) const {

	Vector3 n = u.getNormalized();
	Coordtype d = n.dot(*this);
	return *this - (n * (2.0f*d));
}

Vector3 Vector3::project (const Vector3& u) const {
	Vector3 n = u.getNormalized();
	Coordtype d = n.dot(*this);
	return *this - (n * d);
}

Coordtype Vector3::length () const {

	return Math::Sqrt(x*x + y*y + z*z);
}

Coordtype Vector3::lengthSquared () const {
	return x*x + y*y + z*z;
}

Coordtype  Vector3::distance (const Vector3& u) const {
	return (*this - u).length();
}

Coordtype Vector3::angle (const Vector3& u) const {

	Coordtype len0 = length();
	Coordtype len1 = u.length();
	Coordtype dot = x*u.x + y*u.y + z*u.z;
	Coordtype cosa = Math::Clamp(dot / (len0 * len1), -1.0f, 1.0f);
	return Math::Acos(cosa);
}

Coordtype Vector3::angleSigned (const Vector3& u, const Vector3& v) const {
	Coordtype ang = (*this).angle(u);
	Vector3 thisxu = (*this).cross(u);
	return (thisxu.dot(v) > 0.0f) ? ang : -ang;
}

Vector3& Vector3::operator = (const Vector3& u) {

	x = u.x;
	y = u.y;
	z = u.z;
	return *this;
}

bool Vector3::operator == (const Vector3& u) const {
	return x == u.x && y == u.y && z == u.z;
}

bool Vector3::operator != (const Vector3& u) const {
	return x != u.x || y != u.y || z != u.z;
}

Coordtype Vector3::operator [] (int i) const {
	Assert(i >= 0 && i < 4);
	return c[i];
}

Coordtype& Vector3::operator [] (int i) {
	Assert(i >= 0 && i < 4);
	return c[i];
}

bool Vector3::operator <  (const Vector3& u) const {
	if(x < u.x) return true;
	if(x > u.x) return false;

	if(y < u.y) return true;
	if(y > u.y) return false;

	if(z < u.z) return true;
	return false;
}

Vector3 Vector3::operator - () const {
	return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator + (const Vector3& u) const {
	return sum(u);
}

Vector3 Vector3::operator - (const Vector3& u) const {
	return subtract(u);
}

Coordtype Vector3::operator * (const Vector3& u) const {
	return dot(u);
}

Vector3 Vector3::operator % (const Vector3& u) const {
	return cross(u);
}

Vector3 Vector3::operator * (Coordtype lambda) const {
	return Vector3(x*lambda, y*lambda, z*lambda);
}

Vector3 Vector3::operator / (Coordtype lambda) const {
	return Vector3(x/lambda, y/lambda, z/lambda);
}

Vector3& Vector3::operator += (const Vector3& u) {

	x += u.x;
	y += u.y;
	z += u.z;
	return *this;
}

Vector3& Vector3::operator -= (const Vector3& u) {

	x -= u.x;
	y -= u.y;
	z -= u.z;
	return *this;
}

Vector3& Vector3::operator *= (Coordtype lambda) {

	x *= lambda;
	y *= lambda;
	z *= lambda;
	return *this;
}

Vector3& Vector3::operator /= (Coordtype lambda) {

	x /= lambda;
	y /= lambda;
	z /= lambda;
	return *this;
}

Vector3::operator const Coordtype* () const {
	return this->c;
}

void Vector3::xyz (Coordtype* arr) const {

	arr[0] = x;
	arr[1] = y;
	arr[2] = z;
}

Vector3 Vector3::randomUnit () {
	Coordtype u,v;
	Coordtype r,s;
	Coordtype x,y,z;

	do {
		u = RandomUniform() * 2.0f - 1.0f;
		v = RandomUniform() * 2.0f - 1.0f;
		r = u * u + v * v;
	} while (r >= 1.0f);

	s = 2.0f * Math::Sqrt(1.0f - r);

	x = s * u;
	y = s * v;
	z = 1.0f - 2.0f * r;

	return Vector3(x,y,z);
}

Vector3 Vector3::randomPerturbed (Coordtype theta) const {
	Vector3 rand;
	Vector3 dir = *this;

	do {
		rand = Vector3::randomUnit();
	} while (rand.lengthSquared() <= 0.0);

	dir.normalize();
	rand = rand.project(dir);
	rand.normalize();

	Coordtype a = 1.0f / Math::Tan(theta);

	return (a * dir + rand).getNormalized();
}

// ############################################
// special vectors

const Vector3 Vector3::UNIT_X     = Vector3( 1.0f,  0.0f,  0.0f);
const Vector3 Vector3::UNIT_Y     = Vector3( 0.0f,  1.0f,  0.0f);
const Vector3 Vector3::UNIT_Z     = Vector3( 0.0f,  0.0f,  1.0f);

const Vector3 Vector3::UNIT_NEG_X = Vector3(-1.0f,  0.0f,  0.0f);
const Vector3 Vector3::UNIT_NEG_Y = Vector3( 0.0f, -1.0f,  0.0f);
const Vector3 Vector3::UNIT_NEG_Z = Vector3( 0.0f,  0.0f, -1.0f);

const Vector3 Vector3::ZERO       = Vector3( 0.0f,  0.0f,  0.0f);
const Vector3 Vector3::UNIT_SCALE = Vector3( 1.0f,  1.0f,  1.0f);

// ############################################
// outer functions

Vector3 operator * (Coordtype lambda, const Vector3& u) {
	return Vector3(u.x*lambda, u.y*lambda, u.z*lambda);
}
