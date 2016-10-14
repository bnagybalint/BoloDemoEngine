#pragma once

#include "Assist/Common.h"

typedef float Coordtype;
#define Coordtype_GeneralEps        1e-4f
#define Coordtype_GeneralEpsSquared 1e-8f

struct Math
{
	static const Coordtype B_PI;
	static const Coordtype B_PI_INV;
	static const Coordtype B_2PI;
	static const Coordtype B_2PI_INV;
	static const Coordtype B_E;
	static const Coordtype B_SQRT2;
	static const Coordtype B_SQRT2_INV;
	static const Coordtype B_SQRT3;
	static const Coordtype B_SQRT3_INV;

	static const Coordtype B_INFINITY;
	static const Coordtype B_NEG_INFINITY;
	static const Coordtype B_NAN;

	static const float     B_INF_F32;
	static const double    B_INF_F64;
	static const float     B_NEG_INF_F32;
	static const double    B_NEG_INF_F64;
	static const float     B_NAN_F32;
	static const double    B_NAN_F64;

	template <class T> static T Abs(T x);
	template <class T> static T Min(T x, T y);
	template <class T> static T Max(T x, T y);
	template <class T> static T Clamp(T value, T min, T max);

	static Coordtype Interpolate(Coordtype x, Coordtype y, Coordtype t);
	static Coordtype Fract(Coordtype x);
	static Coordtype Mod(Coordtype x, Coordtype y);

	static Coordtype Pow(Coordtype x, Coordtype power);
	static Coordtype Exp(Coordtype x);
	static Coordtype Sqrt(Coordtype x);
	static Coordtype Log(Coordtype x);

	static Coordtype Sin(Coordtype angRad);
	static Coordtype Cos(Coordtype angRad);
	static Coordtype Tan(Coordtype angRad);

	static Coordtype Acos(Coordtype x);
	static Coordtype Atan2(Coordtype y, Coordtype x);

	static Coordtype Deg2Rad(Coordtype deg);
	static Coordtype Rad2Deg(Coordtype rad);
};

template <class T>
T Math::Abs(T x) 
{
	return x < T(0) ? -x : x;
}

template <class T>
T Math::Min(T x, T y)
{
	return (x < y) ? x : y;
}

template <class T>
T Math::Max(T x, T y)
{
	return (x > y) ? x : y;
}

template <class T>
T Math::Clamp(T value, T min, T max)
{
	return Min(Max(value, min), max);
}

