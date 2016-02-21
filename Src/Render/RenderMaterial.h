#pragma once

#include "Assist/Vector3.hpp"

#include "Render/RenderCommon.h"

class RenderShader;
class RenderConstantBuffer;
class RenderTexture;

class RenderMaterial
{
public:
	RenderMaterial(RenderShader* shader);
	~RenderMaterial();
	
	void setupForRendering();

	RenderShader* getShader() const { return mShader; }

private:

	void updateMaterialBufferData();

private:
public: // TODO HACK

	RenderShader* mShader;
public:/*TODO HACK*/RenderTexture* mDiffuseTexture;
	RenderConstantBuffer* mMaterialBuffer;

	Vector3 mColorDiffuse;
	Vector3 mColorSpecular;
	float mRoughness;
	float mReflectance;
};

