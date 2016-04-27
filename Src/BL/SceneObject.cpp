#include "SceneObject.h"

SceneObject::SceneObject()
	: PROPERTY_INIT(position, Vector3::ZERO)
	, PROPERTY_INIT(orientation, Quaternion::IDENTITY)
	, PROPERTY_INIT(selected, false)
{
}

SceneObject::~SceneObject()
{
}
