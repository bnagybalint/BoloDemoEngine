#pragma once

#include "Assist/Common.h"

#include "BL/DisplayCamera.h"

class SceneObject;

class Scene : public PropertyOwner
{
public:

	Scene();
	DISABLE_COPY(Scene);
	~Scene();

private:

	DisplayCamera* mDisplayCamera;

	Array<SceneObject*> mSceneObjects;
};

