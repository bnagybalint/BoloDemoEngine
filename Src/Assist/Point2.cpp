#include "Point2.h"


Point2::Point2()
{
}

Point2::Point2(Coordtype x, Coordtype y)
	: x(x)
	, y(y)
{
}

Point2::Point2(const Point2& other)
	: x(other.x)
	, y(other.y)
{
}

Point2::~Point2()
{
}

Point2& Point2::operator = (const Point2& other)
{
	x = other.x;
	y = other.y;
	return *this;
}

Point2 Point2::operator - () const
{
	return Point2(-x, -y);
}

Point2 Point2::operator + (const Point2& other) const
{
	return Point2(x + other.x, y + other.y);
}

Point2 Point2::operator - (const Point2& other) const
{
	return Point2(x - other.x, y - other.y);
}

Point2 Point2::operator * (const Point2& other) const
{
	return Point2(x * other.x, y * other.y);
}

Point2 Point2::operator * (Coordtype c) const
{
	return Point2(x * c, y * c);
}

bool Point2::operator == (const Point2& other) const
{
	return (x == other.x) && (y == other.y);
}

bool Point2::operator != (const Point2& other) const
{
	return (x != other.x) || (y != other.y);
}

Point2 operator * (Point2::Coordtype c, const Point2& p)
{
	return Point2(p.x * c, p.y * c);
}
