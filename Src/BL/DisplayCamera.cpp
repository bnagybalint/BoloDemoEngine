#include "DisplayCamera.h"

#include "Render/RenderCamera.h"
#include "Render/RenderManager.h"

DisplayCamera::DisplayCamera()
	: PropertyOwner()
	, PROPERTY_INIT(position, Vector3::ZERO)
	, PROPERTY_INIT(orientation, Quaternion::IDENTITY)
{
	mRenderCamera = RenderManager::getInstance()->createCamera();
	RenderManager::getInstance()->setActiveCamera(mRenderCamera);
}

DisplayCamera::~DisplayCamera()
{
	RenderManager::getInstance()->destroyCamera(mRenderCamera); mRenderCamera = NULL;
}
