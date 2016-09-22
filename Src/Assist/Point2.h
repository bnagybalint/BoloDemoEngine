#pragma once

#include "Assist/Common.h"

class Point2
{
private:
	typedef int32 Coordtype;

	friend Point2 operator * (Coordtype c, const Point2&);

public:

	Point2();
	Point2(Coordtype x, Coordtype y);
	Point2(const Point2& other);
	~Point2();

	Point2& operator = (const Point2& other);

	Point2 operator - () const;
	Point2 operator + (const Point2& other) const;
	Point2 operator - (const Point2& other) const;
	Point2 operator * (const Point2& other) const;

	Point2 operator * (Coordtype c) const;
	
	bool operator == (const Point2& other) const;
	bool operator != (const Point2& other) const;

public:

	Coordtype x;
	Coordtype y;
};

Point2 operator * (Point2::Coordtype c, const Point2&);
