#pragma once

#include "Assist/Common.h"

#include "Assist/Array.h"

#include "Render/RenderCommon.h"

class RenderScene;
class RenderObject;
class RenderCamera;
class RenderViewport;
class RenderConstantBuffer;
class RenderLightSource;

class Matrix4x4;

class RenderSceneRenderer
{
public:

	RenderSceneRenderer();
	~RenderSceneRenderer();

	void renderScene(RenderScene* scene, RenderViewport* viewport, RenderCamera* camera);

private:
	void calcDxViewMatrix(RenderCamera* cam, /*out*/Matrix4x4& mxViewDx);
	void calcDxProjMatrix(RenderViewport* vp, RenderCamera* cam, /*out*/Matrix4x4& mxProjDx);

	void setupMatrices(const Matrix4x4& worldMx, const Matrix4x4& viewMx, const Matrix4x4& projMx);
	void setupLights(const Array<RenderLightSource*>& lights);

private:

	RenderConstantBuffer*    mMatrixBuffer;
	RenderConstantBuffer*    mLightsBuffer;
};

