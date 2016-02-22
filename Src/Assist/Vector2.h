#pragma once

#include "Assist/Common.h"
#include "Assist/MathCommon.h"

class Vector2
{
public:
	Vector2() { }
	Vector2(Coordtype _x, Coordtype _y) : x(_x), y(_y) {}

	virtual ~Vector2() {}

	Vector2& operator=(const Vector2& theOther) {
		x = theOther.x;
		y = theOther.y;

		return *this;
	}

	Vector2 operator+(const Vector2& theOther) const {
		return Vector2(x + theOther.x, y + theOther.y);
	}

	Vector2 operator-(const Vector2& theOther) const {
		return Vector2(x - theOther.x, y - theOther.y);
	}

	Vector2 operator/(Coordtype f) const {
		return Vector2(x / f, y / f);
	}

	Vector2 operator*(Coordtype f) const {
		return Vector2(x * f, y * f);
	}

	Coordtype operator*(const Vector2& theOther) const {
		return ((x * theOther.x) + (y * theOther.y));
	}

	bool operator==(const Vector2& theOther) const {
		return x == theOther.x && y == theOther.y;
	}

	void normalize() {
		Coordtype len = Math::Sqrt(x * x + y * y);
		*this = *this / len;
	}

public:
	Coordtype x;
	Coordtype y;
};