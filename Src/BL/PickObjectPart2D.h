#pragma once

#include "Assist/Common.h"

#include "BL/Pick_Common.h"

class PickObjectPart2D
{
public:

	PickObjectPart2D();
	~PickObjectPart2D();

	virtual bool performPick(const PickInput2D& input, /*out*/PickResult2D& result) const = 0;
};

