#pragma once

#include "Assist/Common.h"

#include "BL/Picker2D.h"

#include "Assist/Vector2.h"

class IPickable2D
{
public:


public:

	IPickable2D();
	virtual ~IPickable2D();

	virtual bool performPick(const Picker2D::PickInput& input, /*out*/Picker2D::PickResult& result) = 0;
};

