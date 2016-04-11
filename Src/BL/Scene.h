#pragma once

#include "Assist/Common.h"

#include "BL/DisplayCamera.h"

class Scene : public PropertyOwner
{
public:

	Scene();
	DISABLE_COPY(Scene);
	~Scene();

private:

	DisplayCamera* mDisplayCamera;
};

