#include "Scene.h"

#include "BL/SceneObject.h"
#include "BL/GeometricObject.h"

Scene::Scene()
	: mDisplayCamera(NULL)
	, mSceneObjects()
{
	mDisplayCamera = PropertyOwner::create<DisplayCamera>();
	mDisplayCamera->position = Vector3(0.0f, 0.3f, -3.0f);

	mSceneObjects.append(PropertyOwner::create<GeometricObject>());
}

Scene::~Scene()
{
	PropertyOwner::destroy(mDisplayCamera); mDisplayCamera = NULL;
	
	for (int i = 0; i < mSceneObjects.size(); i++)
	{
		PropertyOwner::destroy(mSceneObjects[i]); mSceneObjects[i] = NULL;
	}
}
