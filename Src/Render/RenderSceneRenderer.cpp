#include "RenderSceneRenderer.h"

#include "Assist/MathCommon.h"
#include "Assist/Vector3.hpp"
#include "Assist/Quaternion.hpp"
#include "Assist/Matrix3x3.hpp"
#include "Assist/Matrix4x4.hpp"
#include "Assist/Transform.hpp"
#include "Assist/Array.h"

#include "Render/RenderBuffer.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <d3d11.h>
#include <directxmath.h>  

#include "Render/RenderConverter.h"
#include "Render/RenderCamera.h"
#include "Render/RenderViewport.h"
#include "Render/RenderObject.h"
#include "Render/RenderLightSource.h"
#include "Render/RenderScene.h"
#include "Render/RenderManager.h"

namespace {
	struct MatrixBufferType
	{
		DirectX::XMMATRIX mxModelView;
		DirectX::XMMATRIX mxModelViewProj;
		DirectX::XMMATRIX mxNormal;
	};
}

namespace {
	static const int gNumMaxLights = 4;
	struct LightBufferType
	{
		DirectX::XMVECTOR lightPosition;
		DirectX::XMVECTOR lightDirection;
		DirectX::XMVECTOR lightColor;
	};
}

RenderSceneRenderer::RenderSceneRenderer()
	: mMatrixBuffer(NULL)
	, mLightsBuffer(NULL)
{
	mMatrixBuffer = RENDER_NEW(RenderConstantBuffer)();
	mLightsBuffer = RENDER_NEW(RenderConstantBuffer)();
}

RenderSceneRenderer::~RenderSceneRenderer()
{
	RENDER_DELETE(mMatrixBuffer, RenderConstantBuffer); mMatrixBuffer = NULL;
	RENDER_DELETE(mLightsBuffer, RenderConstantBuffer); mLightsBuffer = NULL;
}

void RenderSceneRenderer::renderScene(RenderScene* scene, RenderViewport* viewport, RenderCamera* camera)
{
	Assert(viewport && viewport && scene);

	Matrix4x4 viewMxDx;
	calcDxViewMatrix(camera, viewMxDx);
	Matrix4x4 projMxDx;
	calcDxProjMatrix(viewport, camera, projMxDx);

	Array<RenderObject*> objects = scene->getObjects();
	Array<RenderLightSource*> lights = scene->getLights();

	// Setup light buffer
	setupLights(lights);

	for (int i = 0; i < objects.size(); ++i)
	{
		RenderObject* ro = objects[i];

		// Setup matrix buffer
		setupMatrices(ro->getWorldTransform().toMatrix4x4(), viewMxDx, projMxDx);

		// Setup geometry and material
		ro->setupForRendering();
		// Actually render object
		ro->render();
	}
}

void RenderSceneRenderer::setupMatrices(const Matrix4x4& worldMx, const Matrix4x4& viewMx, const Matrix4x4& projMx)
{
	Assert(mMatrixBuffer);

	Matrix4x4 modelViewMx = viewMx * worldMx;
	Matrix4x4 modelViewProjMx = projMx * modelViewMx;
	Matrix4x4 normalMx = modelViewMx.inverse().transpose();

	MatrixBufferType buf;
	buf.mxModelView     = RenderConverter::convertToDX(modelViewMx);
	buf.mxModelViewProj = RenderConverter::convertToDX(modelViewProjMx);
	buf.mxNormal        = RenderConverter::convertToDX(normalMx);

	mMatrixBuffer->setData(&buf, sizeof(MatrixBufferType));
	mMatrixBuffer->bind(RenderManager::ConstantBufferSlot::MatrixBufferSlot);
}

void RenderSceneRenderer::setupLights(const Array<RenderLightSource*>& lights)
{
	Assert(mLightsBuffer);

	LightBufferType buf[gNumMaxLights];

	Assert(lights.size() < gNumMaxLights);
	for (int lightIdx = 0; lightIdx < gNumMaxLights; lightIdx++)
	{
		if (lightIdx < lights.size())
		{
			// TODO cleanup
			Transform lightTrans = lights[lightIdx]->getWorldTransform();
			Color intensity = lights[lightIdx]->getIntensity();

			buf[lightIdx].lightPosition  = RenderConverter::convertToDX(lightTrans.getPosition());
			buf[lightIdx].lightDirection = RenderConverter::convertToDX(lightTrans * Vector3::UNIT_Z);
			buf[lightIdx].lightColor     = RenderConverter::convertToDX(intensity);
		}
		else
		{
			Memory::Memset(&buf[lightIdx], 0x00, sizeof(LightBufferType));
		}
	}

	mLightsBuffer->setData(&buf, gNumMaxLights*sizeof(LightBufferType));
	mLightsBuffer->bind(RenderManager::ConstantBufferSlot::LightBufferSlot);
}

void RenderSceneRenderer::calcDxViewMatrix(RenderCamera* cam, /*out*/Matrix4x4& mxViewDx)
{
	Assert(Math::Abs(cam->getWorldScale().x - 1.0f) < 1e-3f); // no scale allowed
	Assert(Math::Abs(cam->getWorldScale().y - 1.0f) < 1e-3f); // no scale allowed
	Assert(Math::Abs(cam->getWorldScale().z - 1.0f) < 1e-3f); // no scale allowed

	const Transform& cameraWorld = cam->getWorldTransform();

	// Camera local axes (RH):
	//  +x: left
	//  +y: up
	//  +z: forward
	// 
	// View matrix axes (RH, OpenGL reference):
	//  +x: right
	//  +y: up
	//  -z: forward

	Quaternion qCamInv = cameraWorld.getOrientation().inverse(); // inverse of camera world orientation ...
	Quaternion qRot    = Quaternion(0.0f, 0.0f, 1.0f, 0.0f);     // ... and 180 deg rotation around y ...
	Quaternion qView   = qRot * qCamInv;                         // ... brings the camera facing -z

	Matrix3x3 mxViewRot = qView.toMatrix3x3();
	Vector3   mxViewPos = mxViewRot * (-cameraWorld.getPosition());
	
	mxViewDx = Matrix4x4::createFromParts(mxViewRot, mxViewPos, Vector3::ZERO, 1.0);
}

void RenderSceneRenderer::calcDxProjMatrix(RenderViewport* vp, RenderCamera* cam, /*out*/Matrix4x4& mxProjDx)
{
	float aspect = float(vp->getWidth()) / float(vp->getHeight()); 
	Matrix4x4 mxProj = Matrix4x4::createProjection(cam->getFovY(), aspect, cam->getNearDistance(), cam->getFarDistance());

	// Bring the z component range from OpenGL (-1,1) to DX (0,1)
	mxProj(2, 0) = 0.5f * (mxProj(2, 0) + mxProj(3, 0));
	mxProj(2, 1) = 0.5f * (mxProj(2, 1) + mxProj(3, 1));
	mxProj(2, 2) = 0.5f * (mxProj(2, 2) + mxProj(3, 2));
	mxProj(2, 3) = 0.5f * (mxProj(2, 3) + mxProj(3, 3));

	mxProjDx = mxProj;
}
