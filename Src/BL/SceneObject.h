#pragma once

#include "Assist/Common.h"
#include "Assist/PropertyOwner.h"
#include "Assist/Vector3.hpp"
#include "Assist/Quaternion.hpp"

class SceneObject : public PropertyOwner
{
public:

	SceneObject();
	virtual ~SceneObject();

public:

	Property<Vector3> position;
	Property<Quaternion> orientation;

	Property<bool> selected;
};

