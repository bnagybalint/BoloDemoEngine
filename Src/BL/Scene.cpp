#include "Scene.h"

Scene::Scene()
	: mDisplayCamera(NULL)
{
	mDisplayCamera = new DisplayCamera();
}

Scene::~Scene()
{
	delete mDisplayCamera; mDisplayCamera = NULL;
}
