#include "RenderObject.h"

#include "Assist/Common.h"

#include "Render/RenderMaterial.h"
#include "Render/RenderMesh.h"

RenderObject::RenderObject(RenderScene* scene, RenderMesh* mesh, RenderMaterial* material)
	: RenderSceneElement(scene)
	, mMesh(mesh)
	, mMaterial(material)
{
}

RenderObject::~RenderObject()
{
#if BDE_GLOBAL_ENABLE_NICE_DESTROY
#endif
}

void RenderObject::setupForRendering()
{
	mMaterial->setupForRendering();
	mMesh->setupForRendering(mMaterial);
}

void RenderObject::render()
{
	mMesh->render();
}
