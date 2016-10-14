#include "RenderScene.h"

#include "Assist/Matrix3x3.hpp"
#include "Assist/Matrix4x4.hpp"

#include "Render/RenderCommon.h"
#include "Render/RenderObject.h"
#include "Render/RenderLightSource.h"
#include "Render/RenderCamera.h"
#include "Render/RenderViewport.h"
#include "Render/RenderBuffer.h"
#include "Render/RenderManager.h"
#include "Render/RenderConverter.h"
#include "Render/RenderSceneRenderer.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <directxmath.h>

RenderScene::RenderScene()
	: mRenderer(NULL)
	, mObjects()
	, mLights()
{
	mRenderer = RENDER_NEW(RenderSceneRenderer)();
}

RenderScene::~RenderScene()
{
	RENDER_DELETE(mRenderer, RenderSceneRenderer); mRenderer = NULL;

	Assert(mObjects.isEmpty());
	Assert(mLights.isEmpty());
}

void RenderScene::render(RenderViewport* viewport, RenderCamera* camera)
{
	mRenderer->renderScene(this, viewport, camera);
}

RenderObject* RenderScene::createObject(RenderMesh* mesh, RenderMaterial* mat)
{
	RenderObject* ro = RENDER_NEW(RenderObject)(this, mesh, mat);
	mObjects.append(ro);
	return ro;
}
RenderLightSource* RenderScene::createLightSource()
{
	RenderLightSource* light = RENDER_NEW(RenderLightSource)(this);
	mLights.append(light);
	return light;
}
RenderCamera* RenderScene::createCamera()
{
	return RENDER_NEW(RenderCamera)(this);
}
void RenderScene::destroyObject(RenderObject* obj)
{
	Assert(mObjects.eContains(obj));
	mObjects.eRemoveItemUnordered(obj);
	RENDER_DELETE(obj, RenderObject);
}
void RenderScene::destroyLightSource(RenderLightSource* light)
{
	Assert(mLights.eContains(light));
	mLights.eRemoveItemUnordered(light);
	RENDER_DELETE(light, RenderLightSource);
}
void RenderScene::destroyCamera(RenderCamera* cam)
{
	RENDER_DELETE(cam, RenderCamera);
}
