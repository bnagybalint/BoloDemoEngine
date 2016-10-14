#pragma once

#include "Render/RenderSceneElement.h"

class RenderMesh;
class RenderMaterial;
class RenderScene;

class RenderObject : public RenderSceneElement
{
public:
	RenderObject(RenderScene* scene, RenderMesh* mesh, RenderMaterial* material);
	~RenderObject();

	void setupForRendering();

	void render();

	RenderMesh* getMesh() const { return mMesh; }
	RenderMaterial* getMaterial() const { return mMaterial; }

private:

	RenderMesh* mMesh;
	RenderMaterial* mMaterial;
};

