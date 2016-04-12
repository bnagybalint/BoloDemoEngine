#include "RenderShader.h"

#include "Assist/Memory.h"

#include "Render/RenderCommon.h"
#include "Render/RenderManager.h"

#include <d3d11.h>
#include <d3dcompiler.h>

#if BDE_RENDER_DX_DEBUG
#include <string>
#endif

RenderShader::RenderShader()
#if BDE_GLOBAL_ENABLE_NICE_INIT
	: mDxVertexShader(NULL)
	, mDxPixelShader(NULL)
	, mDxSamplerStateDiffuse(NULL)
	, mDxVertexShaderBufferData(NULL)
	, mDxVertexShaderBufferDataSize(0)
#endif
{
}

RenderShader::~RenderShader()
{
#if BDE_GLOBAL_ENABLE_NICE_DESTROY
	if (mDxVertexShader) { mDxVertexShader->Release(); mDxVertexShader = NULL; }
	if (mDxPixelShader) { mDxPixelShader->Release(); mDxPixelShader = NULL; }
	if (mDxSamplerStateDiffuse) { mDxSamplerStateDiffuse->Release(); mDxSamplerStateDiffuse = NULL; }
	if (mDxVertexShaderBufferData)
	{
		delete[] mDxVertexShaderBufferData; mDxVertexShaderBufferData = NULL;
		mDxVertexShaderBufferDataSize = 0;
	}
#endif
}

void RenderShader::initialize(const char* vertexShaderSource, const char* pixelShaderSource)
{
	ID3D10Blob* vertexShaderBuffer = NULL;
	ID3D10Blob* pixelShaderBuffer = NULL;

#if BDE_RENDER_DX_DEBUG
	ID3D10Blob* errorMessage;
#endif

	UINT compileFlags = D3DCOMPILE_ENABLE_STRICTNESS;

	HRESULT hr;
	// compile VS
	hr = D3DCompile(
		/*source      =*/vertexShaderSource,
		/*source size =*/strlen(vertexShaderSource),
#if BDE_RENDER_DX_DEBUG
		/*sourceName  =*/"VERTEX SHADER",
#else
		/*sourceName  =*/NULL,
#endif
		/*defines     =*/NULL,
		/*includes    =*/NULL,
		/*entrypoint  =*/"v",
		/*target      =*/"vs_5_0",
		/*flags1      =*/compileFlags,
		/*flags2      =*/0,
		/*out ppCode  =*/&vertexShaderBuffer,
#if BDE_RENDER_DX_DEBUG
		/*out ppError =*/&errorMessage);
#else
		/*out ppError =*/NULL);
#endif

#if BDE_RENDER_DX_DEBUG
	if (FAILED(hr))
		AssertMsg(false, std::string((unsigned char*)errorMessage->GetBufferPointer(), (unsigned char*)errorMessage->GetBufferPointer() + errorMessage->GetBufferSize()).c_str());
#endif

	// compile PS
	hr = D3DCompile(
		/*source      =*/pixelShaderSource,
		/*source size =*/strlen(pixelShaderSource),
#if BDE_RENDER_DX_DEBUG
		/*sourceName  =*/"PIXEL SHADER",
#else
		/*sourceName  =*/NULL,
#endif
		/*defines     =*/NULL,
		/*includes    =*/NULL,
		/*entrypoint  =*/"p",
		/*target      =*/"ps_5_0",
		/*flags1      =*/compileFlags,
		/*flags2      =*/0,
		/*out ppCode  =*/&pixelShaderBuffer,
#if BDE_RENDER_DX_DEBUG
		/*out ppError =*/&errorMessage);
#else
		/*out ppError =*/NULL);
#endif

#if BDE_RENDER_DX_DEBUG
	if (FAILED(hr))
		AssertMsg(false, std::string((unsigned char*)errorMessage->GetBufferPointer(), (unsigned char*)errorMessage->GetBufferPointer() + errorMessage->GetBufferSize()).c_str());
#endif

	DX_GetDevice(dxdev);

	DX_SafeCall(dxdev->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &mDxVertexShader));
	DX_SafeCall(dxdev->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &mDxPixelShader));

	// store vertex shader code for later
	mDxVertexShaderBufferDataSize = vertexShaderBuffer->GetBufferSize();
	mDxVertexShaderBufferData = new unsigned char[mDxVertexShaderBufferDataSize];
	Memory::Memcopy(&mDxVertexShaderBufferData[0], vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize());

#if BDE_GLOBAL_ENABLE_NICE_DESTROY
	vertexShaderBuffer->Release(); vertexShaderBuffer = NULL;
	pixelShaderBuffer->Release(); pixelShaderBuffer = NULL;
#endif

	D3D11_SAMPLER_DESC samplerDesc;
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
	DX_SafeCall(dxdev->CreateSamplerState(&samplerDesc, &mDxSamplerStateDiffuse));
}

void RenderShader::setupForRendering()
{
	DX_GetDeviceContext(dxctx);
	dxctx->VSSetShader(mDxVertexShader, NULL, 0);
	dxctx->PSSetShader(mDxPixelShader, NULL, 0);

	//dxctx->VSSetSamplers(RenderManager::ShaderResourceSlot::DiffuseColorTextureSlot, 1, &mDxSamplerStateDiffuse);
	dxctx->PSSetSamplers(RenderManager::ShaderResourceSlot::DiffuseColorTextureSlot, 1, &mDxSamplerStateDiffuse);
}
