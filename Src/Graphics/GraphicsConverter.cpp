#include "GraphicsConverter.h"

#include "Assist/Vector2.h"
#include "Assist/Color.h"

/*static*/ D2D1_POINT_2F GraphicsConverter::convertToD2D(const Vector2& v)
{
	return D2D1::Point2F(v.x, v.y);
}

/*static*/ D2D1_COLOR_F GraphicsConverter::convertToD2D(const Color& c)
{
	return D2D1::ColorF(c.r, c.g, c.b, c.a);
}