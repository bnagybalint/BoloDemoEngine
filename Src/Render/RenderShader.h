#pragma once

#include "Render/RenderCommon.h"

struct ID3D11VertexShader;
struct ID3D11PixelShader;
struct ID3D10Blob;
struct ID3D11SamplerState;

class RenderShader
{
public:

	RenderShader();
	~RenderShader();

	void initialize(const char* vertexShaderSource, const char* pixelShaderSource);

	void setupForRendering();

	const unsigned char* getVertexShaderBuffer() const { return mDxVertexShaderBufferData; };
	unsigned int getVertexShaderBufferSize() const { return mDxVertexShaderBufferDataSize; };

private:

	ID3D11VertexShader* mDxVertexShader;
	ID3D11PixelShader*  mDxPixelShader;
	ID3D11SamplerState* mDxSamplerStateDiffuse;

	// TODO this should be eliminated if possible
	unsigned char* mDxVertexShaderBufferData;
	unsigned int   mDxVertexShaderBufferDataSize;
};
