#pragma once

#include "Assist/Common.h"

#include "BL/Picker2D.h"

#include "Assist/Vector2.h"

class PropertyOwner;

class IPickable2D
{
public:


public:

	IPickable2D(PropertyOwner* propOwner);
	virtual ~IPickable2D();

	// LOCK: property owner's (getPropertyOwner()) lock must be held
	// TODO
	//virtual bool performPick(const Picker2D::PickInput& input, /*out*/Picker2D::PickResult& result) = 0;

	virtual PropertyOwner* getPickedPropertyOwner() const { return mParentPropertyOwner; };

private:

	PropertyOwner* mParentPropertyOwner;
};

