#pragma once

#include "Assist/Common.h"
#include "Assist/Vector3.hpp"

class Color :private Vector4
{
public:

	static Color BLACK;
	static Color RED;
	static Color GREEN;
	static Color BLUE;
	static Color WHITE;

	static Color BLACK_NOALPHA;
	static Color RED_NOALPHA;
	static Color GREEN_NOALPHA;
	static Color BLUE_NOALPHA;
	static Color WHITE_NOALPHA;

public:

	Color();
	Color(const Color& other);
	Color(Coordtype r, Coordtype g, Coordtype b, Coordtype a = Coordtype(1.0));
	~Color();

	Color operator = (const Color& other) const;
	Color operator + (const Color& other) const;
	Color operator - (const Color& other) const;
	Color operator * (const Color& other) const;
	Color operator / (const Color& other) const;

	Color operator * (const Coordtype& scalar) const;
	Color operator / (const Coordtype& scalar) const;

	Coordtype  operator [] (int i) const;
	Coordtype& operator [] (int i);

	operator Coordtype* ();
	operator const Coordtype* () const;

	friend Color operator * (const Coordtype& scalar, const Color& color);
	friend Color operator / (const Coordtype& scalar, const Color& color);

public:
	Coordtype& r;
	Coordtype& g;
	Coordtype& b;
	Coordtype& a;
};

