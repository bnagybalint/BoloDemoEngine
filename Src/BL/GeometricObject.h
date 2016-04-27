#pragma once

#include "Assist/Common.h"

#include "Render/RenderObject.h"

#include "BL/SceneObject.h"
#include "BL/Mesh.h"

class GeometricObject : public SceneObject
{
public:

	GeometricObject();
	virtual ~GeometricObject();

private:

	Mesh* mMesh;

	RenderObject* mRenderObject;
};

