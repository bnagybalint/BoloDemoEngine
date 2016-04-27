#include "DisplayCamera.h"

#include "Render/RenderCamera.h"
#include "Render/RenderManager.h"

DisplayCamera::DisplayCamera()
	: PropertyOwner()
	, PROPERTY_INIT(position, Vector3::ZERO)
	, PROPERTY_INIT(orientation, Quaternion::IDENTITY)
	, mRenderCamera(NULL)
{
	mRenderCamera = RenderManager::getInstance()->createCamera();
	RenderManager::getInstance()->setActiveCamera(mRenderCamera);

	mRenderCamera->setWorldPosition(position);
	mRenderCamera->setCameraAxes(orientation.getValue() * Vector3::UNIT_Z, orientation.getValue() * Vector3::UNIT_Y);

	propertyChangedEvent += PropertyOwner::PropertyListenerDelegate(this, &DisplayCamera::onPropertyChanged);
}

DisplayCamera::~DisplayCamera()
{
	RenderManager::getInstance()->destroyCamera(mRenderCamera); mRenderCamera = NULL;
}

void DisplayCamera::onPropertyChanged(PropertyOwner* propOwner, PropertyBase* prop)
{
	Assert(propOwner == this);

	if (prop->is(position))
	{
		mRenderCamera->setWorldPosition(position);
	}
	else if(prop->is(orientation))
	{
		mRenderCamera->setWorldOrientation(orientation);
	}
}
