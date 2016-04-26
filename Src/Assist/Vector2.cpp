#include "Vector2.h"

/*static*/ const Vector2 Vector2::UNIT_X     = Vector2(1.0f, 0.0f);
/*static*/ const Vector2 Vector2::UNIT_Y     = Vector2(0.0f, 1.0f);
/*static*/ const Vector2 Vector2::UNIT_NEG_X = Vector2(-1.0f, 0.0f);
/*static*/ const Vector2 Vector2::UNIT_NEG_Y = Vector2(0.0f, -1.0f);
/*static*/ const Vector2 Vector2::ZERO       = Vector2(0.0f, 0.0f);
/*static*/ const Vector2 Vector2::UNIT_SCALE = Vector2(1.0f, 1.0f);


Vector2::Vector2()
{
}

Vector2::Vector2(Coordtype x0, Coordtype y0)
	: x(x0)
	, y(y0)
{
}

Vector2::~Vector2()
{
}

Vector2& Vector2::operator = (const Vector2& theOther)
{
	x = theOther.x;
	y = theOther.y;

	return *this;
}

Vector2 Vector2::operator - () const
{
	return Vector2(-x, -y);
}

Vector2 Vector2::operator + (const Vector2& theOther) const
{
	return Vector2(x + theOther.x, y + theOther.y);
}

Vector2 Vector2::operator - (const Vector2& theOther) const
{
	return Vector2(x - theOther.x, y - theOther.y);
}

Vector2 Vector2::operator / (Coordtype f) const
{
	return Vector2(x / f, y / f);
}

Vector2 Vector2::operator * (Coordtype f) const
{
	return Vector2(x * f, y * f);
}

Coordtype Vector2::operator * (const Vector2& theOther) const
{
	return ((x * theOther.x) + (y * theOther.y));
}

bool Vector2::operator == (const Vector2& theOther) const
{
	return x == theOther.x && y == theOther.y;
}

void Vector2::normalize()
{
	Coordtype len = Math::Sqrt(x * x + y * y);
	*this = *this / len;
}

Vector2 Vector2::rotated(float angleRad) const
{
	float ca = Math::Cos(angleRad);
	float sa = Math::Sin(angleRad);

	return Vector2(x*ca - y*sa, x*sa + y*ca);
}
