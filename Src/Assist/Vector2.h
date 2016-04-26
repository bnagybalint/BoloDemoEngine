#pragma once

#include "Assist/Common.h"
#include "Assist/MathCommon.h"

class Vector2
{
public:

	// special vectors
	static const Vector2 UNIT_X;
	static const Vector2 UNIT_Y;
	static const Vector2 UNIT_NEG_X;
	static const Vector2 UNIT_NEG_Y;
	static const Vector2 ZERO;
	static const Vector2 UNIT_SCALE;

public:

	Vector2();
	Vector2(Coordtype x0, Coordtype y0);

	virtual ~Vector2();

	Vector2& operator = (const Vector2& theOther);
	Vector2 operator - () const;
	Vector2 operator + (const Vector2& theOther) const;
	Vector2 operator - (const Vector2& theOther) const;
	Vector2 operator / (Coordtype f) const;
	Vector2 operator * (Coordtype f) const;
	Coordtype operator * (const Vector2& theOther) const;
	bool operator == (const Vector2& theOther) const;

	void normalize();

	Vector2 rotated(float angleRad) const;

public:
	Coordtype x;
	Coordtype y;
};