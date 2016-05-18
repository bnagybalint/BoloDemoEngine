#pragma once

#include "Assist/Common.h"

#include "BL/IPickable2D.h"
#include "BL/Picker2D.h"

class PickCalculator2D
{
public:

	static bool pickRectangle(const Vector2& rectMin, const Vector2& rectMax, const Picker2D::PickInput& input, /*out*/Picker2D::PickResult& result);
	static bool pickLine(const Vector2& startPoint, const Vector2& endPoint, const Picker2D::PickInput& input, /*out*/Picker2D::PickResult& result);

private:

	PickCalculator2D();
	~PickCalculator2D();
};

