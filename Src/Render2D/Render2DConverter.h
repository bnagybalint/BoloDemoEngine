#pragma once

#include "Assist/Common.h"

#include "Render2D/Render2DCommon.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <d2d1.h>

class Vector2;
class Color;

struct Render2DConverter
{
	static D2D1_POINT_2F convertToD2D(const Vector2& v);
	static D2D1_COLOR_F convertToD2D(const Color& c);
};
