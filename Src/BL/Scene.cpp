#include "Scene.h"

#include "BL/SceneObject.h"
#include "BL/GeometricObject.h"

Scene::Scene()
	: mDisplayCamera(NULL)
{
	mDisplayCamera = new DisplayCamera();
	mDisplayCamera->position = Vector3(0.0f, 0.3f, -3.0f);

	mSceneObjects.append(new GeometricObject());
}

Scene::~Scene()
{
	delete mDisplayCamera; mDisplayCamera = NULL;
}
