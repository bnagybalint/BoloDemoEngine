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

/*static*/ D2D1_MATRIX_3X2_F GraphicsConverter::createTransformD2D(const Vector2& position, float rotationDeg, float scale)
{
	D2D1_MATRIX_3X2_F rotationMx = D2D1::Matrix3x2F::Rotation(rotationDeg, D2D1::Point2F(0.0f, 0.0f));
	D2D1_MATRIX_3X2_F translationMx = D2D1::Matrix3x2F::Translation(position.x, position.y);
	D2D1_MATRIX_3X2_F scaleMx       = D2D1::Matrix3x2F::Scale(scale, scale);
	return translationMx * rotationMx * scaleMx;
}
