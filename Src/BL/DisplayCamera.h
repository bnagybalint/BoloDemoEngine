#pragma once

#include "Assist/Common.h"
#include "Assist/PropertyOwner.h"
#include "Assist/Vector3.hpp"
#include "Assist/Quaternion.hpp"

class RenderCamera;

class DisplayCamera	: public PropertyOwner
{
public:

	DisplayCamera();
	DISABLE_COPY(DisplayCamera);
	~DisplayCamera();

public:

	Property<Vector3> position;
	Property<Quaternion> orientation;

private:

	void onPropertyChanged(PropertyOwner* propOwner, PropertyBase* prop);

private:

	// Render
	RenderCamera* mRenderCamera;
};

