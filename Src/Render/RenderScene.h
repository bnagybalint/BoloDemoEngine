#pragma once

#include "Assist/Common.h"

#include "Assist/Array.h"

class RenderObject;
class RenderCamera;
class RenderLightSource;
class RenderMesh;
class RenderMaterial;
class RenderViewport;
class RenderCamera;

class RenderSceneRenderer;

class RenderScene
{
public:

	RenderScene();
	~RenderScene();

	void render(RenderViewport* viewport, RenderCamera* camera);

	RenderObject*      createObject(RenderMesh* mesh, RenderMaterial* mat);
	RenderLightSource* createLightSource();
	RenderCamera*      createCamera();

	void destroyObject(RenderObject* obj);
	void destroyLightSource(RenderLightSource* light);
	void destroyCamera(RenderCamera* cam);

	// TODO return iterators instead
	const Array<RenderObject*>& getObjects() const { return mObjects; }
	const Array<RenderLightSource*>& getLights() const { return mLights; }

private:

	RenderSceneRenderer* mRenderer;

	Array<RenderObject*> mObjects;
	Array<RenderLightSource*> mLights;
};

