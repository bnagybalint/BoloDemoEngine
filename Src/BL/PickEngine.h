#pragma once

#include "Assist/Common.h"
#include "Assist/Vector2.h"

#include "BL/IPickable.h"

class PickEngine
{
public:

	static bool pickRectangle(const Vector2& rectMin, const Vector2& rectMax, /*out*/IPickable2D::PickResult& result);
	static bool pickLine(const Vector2& startPoint, const Vector2& endPoint, /*out*/IPickable2D::PickResult& result);
};

