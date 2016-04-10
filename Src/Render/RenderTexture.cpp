#include "RenderTexture.h"

#include "Assist/Common.h"
#include "Assist/Memory.h"

#include "Render/RenderCommon.h"
#include "Render/RenderManager.h"

#include <d3d11.h>

RenderTexture::RenderTexture()
	: mData(NULL)
	, mDataHeight(0)
	, mDataWidth(0)
	, mDxTexture(NULL)
	, mDxTextureView(NULL)
{
}

RenderTexture::~RenderTexture()
{
#if BDE_GLOBAL_ENABLE_NICE_DESTROY
	if (mDxTexture)
		releaseTexture();
#endif
}

void RenderTexture::setData(uint32* dataRGBA32, unsigned int height, unsigned int width)
{
	Assert(dataRGBA32);
	Assert(height > 0);
	Assert(width > 0);
	if (!mDxTexture)
	{
		// uninitialized buffer
		createTexture(dataRGBA32, height, width);
	}
	else if (mDataWidth == width && mDataHeight == height)
	{
		releaseTexture();
		createTexture(dataRGBA32, height, width);
	}
	else
	{
		fillTexture(dataRGBA32);
	}
}

void RenderTexture::createTexture(uint32* dataRGBA32, unsigned int height, unsigned int width)
{
	mDataHeight = height;
	mDataWidth = width;

	mData = new uint32[mDataHeight*mDataWidth];
	Memory::Memcopy(mData, dataRGBA32, mDataHeight*mDataWidth*sizeof(uint32));

	D3D11_TEXTURE2D_DESC textureDesc;
	textureDesc.Height = height;
	textureDesc.Width = width;
	textureDesc.MipLevels = 0;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

	DX_GetDevice(dxdev);
	DX_SafeCall(dxdev->CreateTexture2D(&textureDesc, NULL, &mDxTexture));

	DX_GetDeviceContext(dxctx);
	UINT rowPitch = mDataWidth * sizeof(uint32);
	dxctx->UpdateSubresource(mDxTexture, 0, NULL, mData, rowPitch, 0);

	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
	shaderResourceViewDesc.Format = textureDesc.Format;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = UINT(-1);
	DX_SafeCall(dxdev->CreateShaderResourceView(mDxTexture, &shaderResourceViewDesc, &mDxTextureView));

	fillTexture(dataRGBA32);
}

void RenderTexture::fillTexture(uint32* dataRGBA32)
{
	(void)dataRGBA32;
	Unimplemented(); // TODO not complete?

	DX_GetDeviceContext(dxctx);
	dxctx->GenerateMips(mDxTextureView);
}

void RenderTexture::releaseTexture()
{
	Assert(mData);
	delete[] mData; mData = NULL;
	Assert(mDxTexture);
	mDxTexture->Release(); mDxTexture = NULL;
	Assert(mDxTextureView);
	mDxTextureView->Release(); mDxTextureView = NULL;
}

void RenderTexture::bindToShader(unsigned int resourceSlot)
{
	DX_GetDeviceContext(dxctx); 
	//dxctx->VSSetShaderResources(resourceSlot, 1, &mDxTextureView);
	dxctx->PSSetShaderResources(resourceSlot, 1, &mDxTextureView);
}
