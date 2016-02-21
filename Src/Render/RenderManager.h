#pragma once

#include "Assist/Common.h"
#include "Assist/Array.h"

#include "Render/RenderCommon.h"

struct ID3D11Device;
struct ID3D11DeviceContext;
struct IDXGISwapChain;
struct ID3D11RenderTargetView;
struct ID3D11Texture2D;
struct ID3D11DepthStencilState;
struct ID3D11DepthStencilView;
struct ID3D11RasterizerState;
struct ID3D11Buffer;
struct ID3D11InfoQueue;

namespace DirectX {
	struct XMMATRIX;
};

class RenderObject;
class RenderCamera;
class RenderViewport;
class RenderLightSource;
class RenderConstantBuffer;

#define DX_GetDevice( dv ) ID3D11Device* dv = RenderManager::getInstance()->getDxDevice()
#define DX_GetDeviceContext( dvc ) ID3D11DeviceContext* dvc = RenderManager::getInstance()->getDxDeviceContext()

class RenderManager
{
public:

	EnumBegin(ConstantBufferSlot, MatrixBufferSlot)
		MatrixBufferSlot = 0,
		MaterialBufferSlot = 1,
		LightBufferSlot = 2,
	EnumEnd(ConstantBufferSlot)

	EnumBegin(ShaderResourceSlot, DiffuseColorTextureSlot)
		DiffuseColorTextureSlot = 0,
		SpecularColorTextureSlot = 1,
		NormalMapTextureSlot = 2,
	EnumEnd(ShaderResourceSlot)

public:

	DECLARE_SINGLETON_HEADER(RenderManager);

public:

	ID3D11Device* getDxDevice() const { return mDxDevice; }
	ID3D11DeviceContext* getDxDeviceContext() const { return mDxDeviceContext; }

	void initDx(HWND windowHandle, unsigned int windowWidth, unsigned int windowHeight);
	void shutdownDx();

	void renderOneFrame();

	void addRenderable(RenderObject* object);
	void addLight(RenderLightSource* light);

	void setActiveCamera(RenderCamera* camera);
	void setActiveViewport(RenderViewport* viewport);

private:

	RenderManager();
	~RenderManager();

private:

	void renderObjects();

	void setupMatrices(const DirectX::XMMATRIX& worldMx, const DirectX::XMMATRIX& viewMx, const DirectX::XMMATRIX& projMx);
	void setupLights();

public:

	// Scene data
	RenderCamera*   mActiveCamera;
	RenderViewport* mActiveViewport;
	Array<RenderObject*> mRenderObjects;
	Array<RenderLightSource*> mLights;

	// DX related stuff
	ID3D11Device*            mDxDevice;
	ID3D11DeviceContext*     mDxDeviceContext;
	IDXGISwapChain*          mDxSwapChain;
	ID3D11RenderTargetView*  mDxRenderTargetView;
	ID3D11Texture2D*         mDxDepthStencilBuffer;
	ID3D11DepthStencilState* mDxDepthStencilState;
	ID3D11DepthStencilView*  mDxDepthStencilView;
	ID3D11RasterizerState*   mDxRasterizerState;

	RenderConstantBuffer*    mMatrixBuffer;
	RenderConstantBuffer*    mLightsBuffer;
};

