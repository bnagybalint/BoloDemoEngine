#include "RenderMaterial.h"

#include "Assist/Common.h"

#include "Render/RenderCommon.h"
#include "Render/RenderShader.h"
#include "Render/RenderBuffer.h"
#include "Render/RenderTexture.h"
#include "Render/RenderManager.h"
#include "Render/RenderConverter.h"

#include <directxmath.h>

namespace
{
	struct MaterialBufferType
	{
		DirectX::XMVECTOR diffuse;
		DirectX::XMVECTOR specular;
		FLOAT             roughness;
		FLOAT             relfectance;
	};
}

RenderMaterial::RenderMaterial(RenderShader* shader)
	: mShader(shader)
	, mDiffuseTexture(NULL)
#if BDE_GLOBAL_ENABLE_NICE_INIT
	, mMaterialBuffer(NULL)
	, mColorDiffuse(Vector3::ZERO)
	, mColorSpecular(Vector3::ZERO)
	, mRoughness(0.0f)
	, mReflectance(0.0f)
#endif
{
	Assert(mShader);

	mMaterialBuffer = RENDER_NEW(RenderConstantBuffer)();
}

RenderMaterial::~RenderMaterial()
{
#if BDE_GLOBAL_ENABLE_NICE_DESTROY
	Assert(mMaterialBuffer);
	RENDER_DELETE(mMaterialBuffer, RenderConstantBuffer); mMaterialBuffer = NULL;

	if (mDiffuseTexture)
	{
		RENDER_DELETE(mDiffuseTexture, RenderTexture); 
		mDiffuseTexture = NULL;
	}
#endif
}

void RenderMaterial::setupForRendering()
{
	// TODO should not be called every frame
	updateMaterialBufferData();

	mShader->setupForRendering();
	mMaterialBuffer->bind(RenderManager::ConstantBufferSlot::MaterialBufferSlot);

// 	Assert(mDiffuseTexture); // currently a must
// 	mDiffuseTexture->bindToShader(RenderManager::ShaderResourceSlot::DiffuseColorTextureSlot);
}

void RenderMaterial::updateMaterialBufferData()
{
	MaterialBufferType buf;
	buf.diffuse = RenderConverter::convertToDX(mColorDiffuse);
	buf.specular = RenderConverter::convertToDX(mColorSpecular);
	buf.roughness = mRoughness;
	buf.relfectance = mReflectance;
	mMaterialBuffer->setData(&buf, sizeof(MaterialBufferType));
}
