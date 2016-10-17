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
class RenderVertexBuffer;
class RenderIndexBuffer;
class RenderMesh;
class RenderShader;
class RenderMaterial;

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

	void initDx(HWND windowHandle);
	void shutdownDx();

	void renderOneFrame();

	RenderVertexBuffer* createVertexBuffer();
	RenderIndexBuffer*  createIndexBuffer();
	RenderMesh*         createMesh(RenderIndexBuffer* indexBuf, RenderVertexBuffer* vertexBuf);
	RenderShader*       createShader();
	RenderMaterial*     createMaterial(RenderShader* shader);

	RenderViewport*     createViewport();
	//RenderTexture*      createTexture();

	void destroyVertexBuffer(RenderVertexBuffer*vb);
	void destroyIndexBuffer(RenderIndexBuffer* ib);
	void destroyMesh(RenderMesh* mesh);
	void destroyShader(RenderShader* shader);
	void destroyMaterial(RenderMaterial* mat);

	void destroyViewport(RenderViewport* vp);
	//void destroyTexture(RenderTexture* tex);

private:

	RenderManager();
	~RenderManager();

public:

	// Scene data
	Array<RenderViewport*>   mViewports;

	// DX related stuff
	ID3D11Device*            mDxDevice;
	ID3D11DeviceContext*     mDxDeviceContext;
	IDXGISwapChain*          mDxSwapChain;
	ID3D11RenderTargetView*  mDxRenderTargetView;
	ID3D11Texture2D*         mDxDepthStencilBuffer;
	ID3D11DepthStencilState* mDxDepthStencilState;
	ID3D11DepthStencilView*  mDxDepthStencilView;
	ID3D11RasterizerState*   mDxRasterizerState;
};

