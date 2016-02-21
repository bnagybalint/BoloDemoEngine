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
  :x(c[0]), y(c[1]), z(c[2]), w(c[3]) { }

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

Vector3& Vector3::copy (Coordtype x0, Coordtype y0, Coordtype z0) {

   x = x0;
   y = y0;
   z = z0;
   w = 0.0f;
   return *this;
}

Vector3& Vector3::copy (Coordtype x0, Coordtype y0, Coordtype z0, Coordtype w0) {

   x = x0;
   y = y0;
   z = z0;
   w = w0;
   return *this;
}

// ############################################
// clear

Vector3& Vector3::clear () {
   x = y = z = w = 0.0f;
   return *this;
}

// ############################################
// addition

Vector3& Vector3::sum (const Vector3& u) {

   x += u.x;
   y += u.y;
   z += u.z;
   return *this;
}

Vector3& Vector3::sum (Coordtype x0, Coordtype y0, Coordtype z0) {

   x += x0;
   y += y0;
   z += z0;
   return *this;
}

Vector3 Vector3::sum (const Vector3& u, const Vector3& v) {
   return Vector3(u.x + v.x, u.y + v.y, u.z + v.z);
}

Vector3 Vector3::sum (Coordtype x0, Coordtype y0, Coordtype z0, Coordtype x1, Coordtype y1, Coordtype z1) {
   return Vector3(x0 + x1, y0 + y1, z0 + z1);
}

// ############################################
// subtraction

Vector3& Vector3::subtract (const Vector3& u) {

   x -= u.x;
   y -= u.y;
   z -= u.z;
   return *this;
}

Vector3& Vector3::subtract (Coordtype x0, Coordtype y0, Coordtype z0) {

   x -= x0;
   y -= y0;
   z -= z0;
   return *this;
}

Vector3 Vector3::subtract (const Vector3& u, const Vector3& v) {
   return Vector3(u.x - v.x, u.y - v.y, u.z - v.z);
}

Vector3 Vector3::subtract (Coordtype x0, Coordtype y0, Coordtype z0, Coordtype x1, Coordtype y1, Coordtype z1) {
   return Vector3(x0 - x1, y0 - y1, z0 - z1);
}

// ############################################
// dot product

Coordtype Vector3::dot (const Vector3& u) const {
   return x*u.x + y*u.y + z*u.z;
}

Coordtype Vector3::dot (Coordtype x0, Coordtype y0, Coordtype z0) const {
   return x*x0 + y*y0 + z*z0;
}

Coordtype Vector3::dot (const Vector3& u, const Vector3& v) {
   return v.x*u.x + v.y*u.y + v.z*u.z;
}

Coordtype Vector3::dot (Coordtype x0, Coordtype y0, Coordtype z0, Coordtype x1, Coordtype y1, Coordtype z1) {
   return x1*x0 + y1*y0 + z1*z0;
}

// ############################################
// cross product

Vector3& Vector3::cross (const Vector3& u) {

   x = y*u.z - z*u.y;
   y = z*u.x - x*u.z;
   z = x*u.y - y*u.x;
   return *this;
}

Vector3& Vector3::cross (Coordtype x0, Coordtype y0, Coordtype z0) {

   x = y*z0 - z*y0;
   y = z*x0 - x*z0;
   z = x*y0 - y*x0;
   return *this;
}

Vector3 Vector3::cross (const Vector3& u, const Vector3& v) {

   return Vector3(u.y*v.z - u.z*v.y,
                  u.z*v.x - u.x*v.z,
                  u.x*v.y - u.y*v.x);
}

Vector3 Vector3::cross (Coordtype x0, Coordtype y0, Coordtype z0, Coordtype x1, Coordtype y1, Coordtype z1) {

   return Vector3(y0*z1 - z0*y1,
                  z0*x1 - x0*z1,
                  x0*y1 - y0*x1);
}

// ############################################
// box product( = this . (v1 x v2) )

Coordtype Vector3::box (const Vector3& u, const Vector3& v) const {

   return x*(u.y*v.z - u.z*v.y) -
          y*(u.x*v.z - u.z*v.x) +
          z*(u.x*v.y - u.y*v.x);
}

Coordtype Vector3::box (Coordtype x0, Coordtype y0, Coordtype z0, Coordtype x1, Coordtype y1, Coordtype z1) const {

   return x*(y0*z1 - z0*y1) -
          y*(x0*z1 - z0*x1) +
          z*(x0*y1 - y0*x1);
}

Coordtype Vector3::box (const Vector3& u, const Vector3& v, const Vector3& w) {

   return u.x*(v.y*w.z - v.z*w.y) -
          u.y*(v.x*w.z - v.z*w.x) +
          u.z*(v.x*w.y - v.y*w.x);
}

Coordtype Vector3::box (Coordtype x0, Coordtype y0, Coordtype z0, Coordtype x1, Coordtype y1, Coordtype z1, Coordtype x2, Coordtype y2, Coordtype z2) {

   return x0*(y1*z2 - z1*y2) -
          y0*(x1*z2 - z1*x2) +
          z0*(x1*y2 - y1*x2);
}

// ############################################
// vector triple product   ( = (this x v1) x v2 )

Vector3& Vector3::triple (const Vector3& u, const Vector3& v) {
   return mix(u, -Vector3::dot(v, u), Vector3::dot(v, *this));
}

Vector3& Vector3::triple (Coordtype x0, Coordtype y0, Coordtype z0, Coordtype x1, Coordtype y1, Coordtype z1) {
   return mix(x0,y0,z0, -Vector3::dot(x1,y1,z1, x0,y0,z0), Vector3::dot(x1,y1,z1, x,y,z));
}

Vector3 Vector3::triple (const Vector3& u, const Vector3& v, const Vector3& w) {
//   TODO: why is (seems) the former wrong?
//   return Vector3::mix(u,v, -Vector3::dot(w,v), Vector3::dot(w,u));
   return Vector3::cross(u,v).cross(w);
}

Vector3 Vector3::triple (Coordtype x0, Coordtype y0, Coordtype z0, Coordtype x1, Coordtype y1, Coordtype z1, Coordtype x2, Coordtype y2, Coordtype z2) {
   return Vector3::mix(x0,y0,z0, x1,y1,z1, -Vector3::dot(x2,y2,z2, x1,y1,z1), Vector3::dot(x2,y2,z2, x0,y0,z0));
}

// ############################################
// normalize

Vector3& Vector3::normalize () {

   Coordtype l = length();
   x /= l;
   y /= l;
   z /= l;
   return *this;
}

Vector3 Vector3::normalized () const {

   Coordtype l = length();
   return Vector3(x/l, y/l, z/l);
}

Vector3 Vector3::normalized (const Vector3& u) {

   Coordtype l = u.length();
   return Vector3(u.x/l, u.y/l, u.z/l);
}

Vector3 Vector3::normalized (Coordtype x0, Coordtype y0, Coordtype z0) {

   Coordtype l = Vector3::length(x0,y0,z0);
   return Vector3(x0/l, y0/l, z0/l);
}

// ############################################
// absolute - get vector with all negative values inverted
Vector3& Vector3::abs () {
   x = Math::Abs(x);
   y = Math::Abs(y);
   z = Math::Abs(z);
   return *this;
}

Vector3 Vector3::abs (const Vector3& u) {
	return Vector3(Math::Abs(u.x), Math::Abs(u.y), Math::Abs(u.z));
}

Vector3 Vector3::abs (Coordtype x0, Coordtype y0, Coordtype z0) {
	return Vector3(Math::Abs(x0), Math::Abs(y0), Math::Abs(z0));
}

// ############################################
// scale - multiply by scalar

Vector3& Vector3::scale (Coordtype lambda) {

   x *= lambda;
   y *= lambda;
   z *= lambda;
   return *this;
}

Vector3 Vector3::scale (const Vector3& u, Coordtype lambda) {
   return Vector3(u.x*lambda, u.y*lambda, u.z*lambda);
}

Vector3 Vector3::scale (Coordtype x0, Coordtype y0, Coordtype z0, Coordtype lambda) {
   return Vector3(x0*lambda, y0*lambda, z0*lambda);
}

// ############################################
// divide - divide by scalar

Vector3& Vector3::divide (Coordtype lambda) {

   x /= lambda;
   y /= lambda;
   z /= lambda;
   return *this;
}

Vector3 Vector3::divide (const Vector3& u, Coordtype lambda) {
   return Vector3(u.x/lambda, u.y/lambda, u.z/lambda);
}

Vector3 Vector3::divide (Coordtype x0, Coordtype y0, Coordtype z0, Coordtype lambda) {
   return Vector3(x0/lambda, y0/lambda, z0/lambda);
}

// ############################################
// coordinate-wise multiplication
Vector3& Vector3::coordWiseMultiply (const Vector3& u){

   x*=u.x;
   y*=u.y;
   z*=u.z;
   w*=u.w;
   return *this;
}

Vector3& Vector3::coordWiseMultiply (Coordtype x0, Coordtype y0, Coordtype z0){

   x*=x0;
   y*=y0;
   z*=z0;
   return *this;
}

Vector3 Vector3::coordWiseMultiply (const Vector3& u, const Vector3& v){
   return Vector3(u.x*v.x, u.y*v.y, u.z*v.z, u.w*v.w);
}

Vector3 Vector3::coordWiseMultiply (Coordtype x0, Coordtype y0, Coordtype z0, Coordtype x1, Coordtype y1, Coordtype z1){
   return Vector3(x0*x1,y0*y1,z0*z1);
}

// ############################################
// interpolate
Vector3& Vector3::interpolate (const Vector3& u, Coordtype t) {

   x = (1.0f-t)*x + t*u.x;
   y = (1.0f-t)*y + t*u.y;
   z = (1.0f-t)*z + t*u.z;
   return *this;
}

Vector3& Vector3::interpolate (Coordtype x0, Coordtype y0, Coordtype z0, Coordtype t) {

   x = (1.0f-t)*x + t*x0;
   y = (1.0f-t)*y + t*y0;
   z = (1.0f-t)*z + t*z0;
   return *this;
}

Vector3 Vector3::interpolate (const Vector3& u, const Vector3& v, Coordtype t) {
   return Vector3( (1.0f-t)*u.x + t*v.x,
                   (1.0f-t)*u.y + t*v.y,
                   (1.0f-t)*u.z + t*v.z );
}

Vector3 Vector3::interpolate (Coordtype x0, Coordtype y0, Coordtype z0, Coordtype x1, Coordtype y1, Coordtype z1, Coordtype t) {
   return Vector3( (1.0f-t)*x0 + t*x1,
                   (1.0f-t)*y0 + t*y1,
                   (1.0f-t)*z0 + t*z1 );
}

// ############################################
// mix(v1,v2,a,b) -> a*v1 + b*v2
Vector3& Vector3::mix (const Vector3& u, Coordtype ta, Coordtype tb) {
   x = ta*x + tb*u.x;
   y = ta*y + tb*u.y;
   z = ta*z + tb*u.z;
   return *this;
}

Vector3& Vector3::mix (Coordtype x0, Coordtype y0, Coordtype z0,Coordtype ta, Coordtype tb)  {
   x = ta*x + tb*x0;
   y = ta*y + tb*y0;
   z = ta*z + tb*z0;
   return *this;
}

Vector3 Vector3::mix (const Vector3& u, const Vector3& v,Coordtype ta, Coordtype tb)  {
   return Vector3(ta*u.x + tb*v.x,
                  ta*u.y + tb*v.y,
                  ta*u.z + tb*v.z);
}

Vector3 Vector3::mix (Coordtype x0, Coordtype y0, Coordtype z0, Coordtype x1, Coordtype y1, Coordtype z1,Coordtype ta, Coordtype tb)  {
   return Vector3(ta*x0 + tb*x1,
                  ta*y0 + tb*y1,
                  ta*z0 + tb*z1);
}

// ############################################
// reflect

Vector3& Vector3::reflect (const Vector3& u) {

   Vector3 n     = Vector3::normalized(u);
   Coordtype dot = Vector3::dot(*this, n);
   x -= 2.0f * dot * n.x;
   y -= 2.0f * dot * n.y;
   z -= 2.0f * dot * n.z;
   return *this;
}

Vector3& Vector3::reflect (Coordtype x0, Coordtype y0, Coordtype z0) {

   Vector3 n     = Vector3::normalized(x0,y0,z0);
   Coordtype dot = Vector3::dot(*this, n);
   x -= 2.0f * dot * n.x;
   y -= 2.0f * dot * n.y;
   z -= 2.0f * dot * n.z;
   return *this;
}

Vector3 Vector3::reflect (const Vector3& u, const Vector3& v) {

   Vector3 n     = Vector3::normalized(v);
   Coordtype dot = Vector3::dot(u, n);
   return Vector3::subtract(u,n.scale(2.0f*dot));
}

Vector3 Vector3::reflect (Coordtype x0, Coordtype y0, Coordtype z0, Coordtype x1, Coordtype y1, Coordtype z1) {

   Vector3 u     = Vector3(x0,y0,z0);
   Vector3 n     = Vector3::normalized(x1,y1,z1);
   Coordtype dot = Vector3::dot(u, n);
   return u.subtract(n.scale(2.0f*dot));
}

// ############################################
// project to plane defined by normal vector

Vector3& Vector3::project (const Vector3& u) {

   Vector3 n     = Vector3::normalized(u);
   Coordtype dot = Vector3::dot(*this, n);
   x -= dot*n.x;
   y -= dot*n.y;
   z -= dot*n.z;
   return *this;
}

Vector3& Vector3::project (Coordtype x0, Coordtype y0, Coordtype z0) {

   Vector3 n     = Vector3::normalized(x0,y0,z0);
   Coordtype dot = Vector3::dot(*this, n);
   x -= dot*n.x;
   y -= dot*n.y;
   z -= dot*n.z;
   return *this;
}

Vector3 Vector3::project (const Vector3& u, const Vector3& v) {

   Vector3 n     = Vector3::normalized(v);
   Coordtype dot = Vector3::dot(u, n);
   return Vector3::subtract(u,n.scale(dot));
}

Vector3 Vector3::project (Coordtype x0, Coordtype y0, Coordtype z0, Coordtype x1, Coordtype y1, Coordtype z1) {

   Vector3 u     = Vector3(x0,y0,z0);
   Vector3 n     = Vector3::normalized(x1,y1,z1);
   Coordtype dot = Vector3::dot(u, n);
   return u.subtract(n.scale(dot));
}

// ############################################
// rotate

Vector3& Vector3::rotate (const Vector3& u, Coordtype theta) {

   Coordtype c = (Coordtype)Math::Cos(theta);
   Coordtype s = (Coordtype)Math::Sin(theta);
   Coordtype mx[12] = {
      u.x*u.x + (1.0f-u.x*u.x)*c,    u.x*u.y*(1.0f-c) - u.z*s,      u.x*u.z*(1.0f-c) + u.y*s,      0.0f,
      u.y*u.x*(1.0f-c) + u.z*s,      u.y*u.y + (1.0f-u.y*u.y)*c,    u.y*u.z*(1.0f-c) - u.x*s,      0.0f,
      u.z*u.x*(1.0f-c) - u.y*s,      u.z*u.y*(1.0f-c) + u.x*s,      u.z*u.z + (1.0f-u.z*u.z)*c,    0.0f
   };

   x = x*mx[0] + y*mx[1] + z*mx[2]  + mx[3];
   y = x*mx[4] + y*mx[5] + z*mx[6]  + mx[7];
   z = x*mx[8] + y*mx[9] + z*mx[10] + mx[11];

   return *this;
}

Vector3& Vector3::rotate (Coordtype x0, Coordtype y0, Coordtype z0, Coordtype theta) {

   Coordtype c = (Coordtype)Math::Cos(theta);
   Coordtype s = (Coordtype)Math::Sin(theta);
   Coordtype mx[12] = {
      x0*x0 + (1.0f-x0*x0)*c,     x0*y0*(1.0f-c) - z0*s,      x0*z0*(1.0f-c) + y0*s,      0.0f,
      y0*x0*(1.0f-c) + z0*s,      y0*y0 + (1.0f-y0*y0)*c,     y0*z0*(1.0f-c) - x0*s,      0.0f,
      z0*x0*(1.0f-c) - y0*s,      z0*y0*(1.0f-c) + x0*s,      z0*z0 + (1.0f-z0*z0)*c,     0.0f
   };

   x = x*mx[0] + y*mx[1] + z*mx[2]  + mx[3];
   y = x*mx[4] + y*mx[5] + z*mx[6]  + mx[7];
   z = x*mx[8] + y*mx[9] + z*mx[10] + mx[11];

   return *this;
}

Vector3 Vector3::rotate (const Vector3& u, const Vector3& v, Coordtype theta) {

   Coordtype c = (Coordtype)Math::Cos(theta);
   Coordtype s = (Coordtype)Math::Sin(theta);
   Coordtype mx[12] = {
      v.x*v.x + (1.0f-v.x*v.x)*c,   v.x*v.y*(1.0f-c) - v.z*s,     v.x*v.z*(1.0f-c) + v.y*s,      0.0f,
      v.y*v.x*(1.0f-c) + v.z*s,     v.y*v.y + (1.0f-v.y*v.y)*c,   v.y*v.z*(1.0f-c) - v.x*s,      0.0f,
      v.z*v.x*(1.0f-c) - v.y*s,     v.z*v.y*(1.0f-c) + v.x*s,     v.z*v.z + (1.0f-v.z*v.z)*c,    0.0f
   };

   return Vector3(u.x*mx[0] + u.y*mx[1] + u.z*mx[2]  + mx[3],
                  u.x*mx[4] + u.y*mx[5] + u.z*mx[6]  + mx[7],
                  u.x*mx[8] + u.y*mx[9] + u.z*mx[10] + mx[11]);
}

Vector3 Vector3::rotate (Coordtype x0, Coordtype y0, Coordtype z0, Coordtype x1, Coordtype y1, Coordtype z1, Coordtype theta) {

   Coordtype c = (Coordtype)Math::Cos(theta);
   Coordtype s = (Coordtype)Math::Sin(theta);
   Coordtype mx[12] = {
      x1*x1 + (1.0f-x1*x1)*c,     x1*y1*(1.0f-c) - z1*s,      x1*z1*(1.0f-c) + y1*s,      0.0f,
      y1*x1*(1.0f-c) + z1*s,      y1*y1 + (1.0f-y1*y1)*c,     y1*z1*(1.0f-c) - x1*s,      0.0f,
      z1*x1*(1.0f-c) - y1*s,      z1*y1*(1.0f-c) + x1*s,      z1*z1 + (1.0f-z1*z1)*c,     0.0f
   };

   return Vector3(x0*mx[0] + y0*mx[1] + z0*mx[2]  + mx[3],
                  x0*mx[4] + y0*mx[5] + z0*mx[6]  + mx[7],
                  x0*mx[8] + y0*mx[9] + z0*mx[10] + mx[11]);
}

// ############################################
// transform

Vector3& Vector3::transform (Coordtype* mx) {

   x = x*mx[0] + y*mx[1] + z*mx[2]  + mx[3];
   y = x*mx[4] + y*mx[5] + z*mx[6]  + mx[7];
   z = x*mx[8] + y*mx[9] + z*mx[10] + mx[11];

   return *this;
}

Vector3 Vector3::transform (const Vector3& u, Coordtype* mx) {

   return Vector3(u.x*mx[0] + u.y*mx[1] + u.z*mx[2]  + mx[3],
                  u.x*mx[4] + u.y*mx[5] + u.z*mx[6]  + mx[7],
                  u.x*mx[8] + u.y*mx[9] + u.z*mx[10] + mx[11]);
}

Vector3 Vector3::transform (Coordtype x0, Coordtype y0, Coordtype z0, Coordtype* mx) {

   return Vector3(x0*mx[0] + y0*mx[1] + z0*mx[2]  + mx[3],
                  x0*mx[4] + y0*mx[5] + z0*mx[6]  + mx[7],
                  x0*mx[8] + y0*mx[9] + z0*mx[10] + mx[11]);
}

// ############################################
// length

Coordtype Vector3::length () const {

	return Math::Sqrt(x*x + y*y + z*z);
}

Coordtype Vector3::length (const Vector3& u) {

   return Math::Sqrt(u.x*u.x + u.y*u.y + u.z*u.z);
}

Coordtype Vector3::length (Coordtype x0, Coordtype y0, Coordtype z0) {

	return Math::Sqrt(x0*x0 + y0*y0 + z0*z0);
}

// ############################################
// length squared

Coordtype Vector3::lengthSquared () const {
   return x*x + y*y + z*z;
}

Coordtype Vector3::lengthSquared (const Vector3& u) {
   return u.x*u.x + u.y*u.y + u.z*u.z;
}

Coordtype Vector3::lengthSquared (Coordtype x0, Coordtype y0, Coordtype z0) {
   return x0*x0 + y0*y0 + z0*z0;
}

// ############################################
// distance

Coordtype  Vector3::distance (const Vector3& u) const {
   return Vector3::length((*this) - u);
}

Coordtype  Vector3::distance (Coordtype x0, Coordtype y0, Coordtype z0) const {
   return Vector3::length(x - x0, y - y0, z - z0);
}

Coordtype  Vector3::distance (const Vector3& u, const Vector3& v) {
   return Vector3::length(u - v);
}

Coordtype  Vector3::distance (Coordtype x0, Coordtype y0, Coordtype z0, Coordtype x1, Coordtype y1, Coordtype z1) {
   return Vector3::length(x0 - x1, y0 - y1, z0 - z1);

}

// ############################################
// angle of two vectors

Coordtype Vector3::angle (const Vector3& u) const {

   Coordtype len0 = length();
   Coordtype len1 = u.length();
   Coordtype dot  = x*u.x + y*u.y + z*u.z;
   Coordtype cosa = Math::Clamp(dot / (len0 * len1), -1.0f, 1.0f);
   return Math::Acos( cosa );
}

Coordtype Vector3::angle (Coordtype x0, Coordtype y0, Coordtype z0) const {

   Coordtype len0 = length();
   Coordtype len1 = Vector3::length(x0,y0,z0);
   Coordtype dot  = x*x0 + y*y0 + z*z0;
   Coordtype cosa = Math::Clamp(dot / (len0 * len1), -1.0f, 1.0f);
   return Math::Acos( cosa );
}

Coordtype Vector3::angle (const Vector3& u, const Vector3& v) {

   Coordtype len0 = u.length();
   Coordtype len1 = v.length();
   Coordtype dot  = u.dot(v);
   Coordtype cosa = Math::Clamp(dot / (len0 * len1), -1.0f, 1.0f);
   return Math::Acos(cosa);
}

Coordtype Vector3::angle (Coordtype x0, Coordtype y0, Coordtype z0, Coordtype x1, Coordtype y1, Coordtype z1) {

   Coordtype len0 = Vector3::length(x0,y0,z0);
   Coordtype len1 = Vector3::length(x1,y1,z1);
   Coordtype dot  = Vector3::dot(x0,y0,z0, x1,y1,z1);
   Coordtype cosa = Math::Clamp(dot / (len0 * len1), -1.0f, 1.0f);
   return Math::Acos(cosa);
}

// ############################################
// signed angle of two vectors on plane
// defined by its normal vector

Coordtype Vector3::angleSigned (const Vector3& u, const Vector3& v) const {
   Coordtype ang = Vector3::angle(*this,u);
   Vector3 thisxu = Vector3::cross(*this,u);
   return (Vector3::dot(thisxu,v) > 0.0f) ? ang : -ang;
}

Coordtype Vector3::angleSigned (Coordtype x0, Coordtype y0, Coordtype z0, Coordtype x1, Coordtype y1, Coordtype z1) const {
   Coordtype ang = Vector3::angle(x,y,z, x0,y0,z0);
   Vector3 thisxu = Vector3::cross(x,y,z, x0,y0,z0);
   return (Vector3::dot(thisxu.x,thisxu.y,thisxu.z,x1,y1,z1) > 0.0f) ? ang : -ang;
}

Coordtype Vector3::angleSigned (const Vector3& u, const Vector3& v, const Vector3& w) {
   Coordtype ang = Vector3::angle(u,v);
   Vector3 uxv = Vector3::cross(u,v);
   return (Vector3::dot(uxv,w) > 0.0f) ? ang : -ang;
}

Coordtype Vector3::angleSigned (Coordtype x0, Coordtype y0, Coordtype z0, Coordtype x1, Coordtype y1, Coordtype z1, Coordtype x2, Coordtype y2, Coordtype z2) {
   Coordtype ang = Vector3::angle(x0,y0,z0, x1,y1,z1);
   Vector3 uxv = Vector3::cross(x0,y0,z0, x1,y1,z1);
   return (Vector3::dot(uxv.x,uxv.y,uxv.z, x2,y2,z2) > 0.0f) ? ang : -ang;
}

// ############################################
// operators overloaded

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
   return c[i];
}

Coordtype& Vector3::operator [] (int i) {
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
   return Vector3(x+u.x, y+u.y, z+u.z);
}

Vector3 Vector3::operator - (const Vector3& u) const {
   return Vector3(x-u.x, y-u.y, z-u.z);
}

Coordtype Vector3::operator * (const Vector3& u) const {
   return x*u.x + y*u.y + z*u.z;
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

// ############################################
// coordinates

void Vector3::xyz (Coordtype* arr) const {

   arr[0] = x;
   arr[1] = y;
   arr[2] = z;
}

// ####################################

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

Vector3& Vector3::randomPerturbed (Coordtype theta) {
   Vector3 rand;

   do {
      rand = Vector3::randomUnit();
   } while(rand.lengthSquared() <= 0.0);

   normalize();
   rand.project(*this).normalize();

   Coordtype a = 1.0f / Math::Tan(theta);

   x = a * x + rand.x;
   y = a * y + rand.y;
   z = a * z + rand.z;

   return this->normalize();
}

Vector3 Vector3::randomPerturbed (const Vector3& u, Coordtype theta) {
   Vector3 rand;
   Vector3 dir = u;

   do {
      rand = Vector3::randomUnit();
   } while (rand.lengthSquared() <= 0.0);

   dir.normalize();
   rand.project(dir).normalize();

   Coordtype a = 1.0f / Math::Tan(theta);

   return (a * dir + rand).normalize();
}

Vector3 Vector3::randomPerturbed (Coordtype x0, Coordtype y0, Coordtype z0, Coordtype theta) {
   Vector3 rand;
   Vector3 dir(x0,y0,z0);

   do {
      rand = Vector3::randomUnit();
   } while (rand.lengthSquared() <= 0.0);

   dir.normalize();
   rand.project(dir).normalize();

   Coordtype a = 1.0f / Math::Tan(theta);

   return (a * dir + rand).normalize();
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
// otuer functions

Vector3 operator * (Coordtype lambda, const Vector3& u) {
   return Vector3(u.x*lambda, u.y*lambda, u.z*lambda);
}
