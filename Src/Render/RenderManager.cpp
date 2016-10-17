#include "RenderManager.h"

#include "Assist/Memory.h"

#include "Render/RenderViewport.h"
#include "Render/RenderCamera.h"
#include "Render/RenderCommon.h"
#include "Render/RenderObject.h" 
#include "Render/RenderLightSource.h"
#include "Render/RenderBuffer.h"
#include "Render/RenderMesh.h" 
#include "Render/RenderShader.h"
#include "Render/RenderMaterial.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <d3d11.h>
#include <directxmath.h>

// Define singleton parts
DEFINE_SINGLETON_IMPL(RenderManager);

RenderManager::RenderManager()
{
#if BDE_GLOBAL_ENABLE_NICE_INIT
	Memory::Memzero(this, sizeof(RenderManager));
#endif
}

RenderManager::~RenderManager()
{
}

void RenderManager::initDx(HWND windowHandle)
{
	RECT rc;
	GetWindowRect(windowHandle, &rc);

	UINT windowWidth = rc.right - rc.left;
	UINT windowHeight = rc.bottom - rc.top;

#if BDE_RENDER_ENABLE_VSYNC
	// Create a DirectX graphics interface factory.
	IDXGIFactory* factory;
	DX_SafeCall(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory));

	// Use the factory to create an adapter for the primary graphics interface (video card).
	IDXGIAdapter* adapter;
	DX_SafeCall(factory->EnumAdapters(0, &adapter));

	// Enumerate the primary adapter output (monitor).
	IDXGIOutput* adapterOutput;
	DX_SafeCall(adapter->EnumOutputs(0, &adapterOutput));

	// Get the number of modes that fit the DXGI_FORMAT_R8G8B8A8_UNORM display format for the adapter output (monitor).
	unsigned int numModes;
	DX_SafeCall(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL));
	DXGI_MODE_DESC* displayModeList = new DXGI_MODE_DESC[numModes];
	DX_SafeCall(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList));

	// Now go through all the display modes and find the one that matches the screen width and height.
	// When a match is found store the numerator and denominator of the refresh rate for that monitor.
	unsigned int rrNumerator, rrDenominator;
	for (unsigned int i = 0; i < numModes; i++) {
		if (displayModeList[i].Width == windowWidth) {
			if (displayModeList[i].Height == windowHeight) {
				rrNumerator = displayModeList[i].RefreshRate.Numerator;
				rrDenominator = displayModeList[i].RefreshRate.Denominator;
			}
		}
	}

# if RENDERMANAGER_GET_ADAPTER_DATA
	// Get the adapter (video card) description.
	DXGI_ADAPTER_DESC adapterDesc;
	DX_SafeCall(adapter->GetDesc(&adapterDesc));
	// Store the dedicated video card memory in megabytes.
	int videomem = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);
# endif // RENDERMANAGER_GET_ADAPTER_DATA

	// Release stuff created in the previous part
	delete[] displayModeList; displayModeList = NULL;
	adapterOutput->Release(); adapterOutput = NULL;
	adapter->Release(); adapter = NULL;
	factory->Release(); factory = NULL;
#endif // BDE_RENDER_ENABLE_VSYNC

	// Initialize the swap chain description.
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	Memory::Memzero(&swapChainDesc, sizeof(swapChainDesc));
	// Set to a single back buffer.
	swapChainDesc.BufferCount = 1;
	// Set the width and height of the back buffer.
	swapChainDesc.BufferDesc.Width = windowWidth;
	swapChainDesc.BufferDesc.Height = windowHeight;
	// Set regular 32-bit surface for the back buffer.
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	// Set the refresh rate of the back buffer.

#if BDE_RENDER_ENABLE_VSYNC
	swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
#else
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
#endif // BDE_RENDER_ENABLE_VSYNC

	// Set the usage of the back buffer.
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	// Set the handle for the window to render to.
	swapChainDesc.OutputWindow = windowHandle;
	// Turn multisampling off.
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	// Set to full screen or windowed mode.

#if BDE_RENDER_ENABLE_FULLSCREEN
	swapChainDesc.Windowed = false;
#else
	swapChainDesc.Windowed = true;
#endif // BDE_RENDER_ENABLE_FULLSCREEN

	// Set the scan line ordering and scaling to unspecified.
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	// Discard the back buffer contents after presenting.
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	// Don't set the advanced flags.
	swapChainDesc.Flags = 0;

	// Set the feature level to DirectX 11.
	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
	// Create the swap chain, Direct3D device, and Direct3D device context.
	UINT deviceFlags = 0;
#if BDE_RENDER_DX_DEBUG
	deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	DX_SafeCall(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, deviceFlags, &featureLevel, 1, D3D11_SDK_VERSION, &swapChainDesc, &mDxSwapChain, &mDxDevice, NULL, &mDxDeviceContext));

	// Get the pointer to the back buffer.
	ID3D11Texture2D* backBufferPtr;
	DX_SafeCall(mDxSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr));

	// Create the render target view with the back buffer pointer.
	DX_SafeCall(mDxDevice->CreateRenderTargetView(backBufferPtr, NULL, &mDxRenderTargetView));

	// Release pointer to the back buffer as we no longer need it.
	backBufferPtr->Release(); backBufferPtr = NULL;

	// Initialize the description of the depth buffer.
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	Memory::Memzero(&depthBufferDesc, sizeof(depthBufferDesc));

	// Set up the description of the depth buffer.
	depthBufferDesc.Width = windowWidth;
	depthBufferDesc.Height = windowHeight;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	// Create the texture for the depth buffer using the filled out description.
	DX_SafeCall(mDxDevice->CreateTexture2D(&depthBufferDesc, NULL, &mDxDepthStencilBuffer));

	// Initialize the description of the stencil state.
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	Memory::Memzero(&depthStencilDesc, sizeof(depthStencilDesc));

	// Set up the description of the stencil state.
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing.
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing.
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create the depth stencil state.
	DX_SafeCall(mDxDevice->CreateDepthStencilState(&depthStencilDesc, &mDxDepthStencilState));

	// Set the depth stencil state.
	mDxDeviceContext->OMSetDepthStencilState(mDxDepthStencilState, 1);

	// Initialize the depth stencil view.
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	Memory::Memzero(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	// Set up the depth stencil view description.
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	// Create the depth stencil view.
	DX_SafeCall(mDxDevice->CreateDepthStencilView(mDxDepthStencilBuffer, &depthStencilViewDesc, &mDxDepthStencilView));

	// Bind the render target view and depth stencil buffer to the output render pipeline.
	mDxDeviceContext->OMSetRenderTargets(1, &mDxRenderTargetView, mDxDepthStencilView);

	// Setup the raster description which will determine how and what polygons will be drawn.
	D3D11_RASTERIZER_DESC rasterizerDesc;
	rasterizerDesc.AntialiasedLineEnable = false;
	rasterizerDesc.CullMode = D3D11_CULL_BACK;
	rasterizerDesc.DepthBias = 0;
	rasterizerDesc.DepthBiasClamp = 0.0f;
	rasterizerDesc.DepthClipEnable = true;
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	// convert to DX: in the mesh, front-facing is defined CCW, which is mirrored by the RH-to-LH transition of the projection transform
	rasterizerDesc.FrontCounterClockwise = true;
	rasterizerDesc.MultisampleEnable = false;
	rasterizerDesc.ScissorEnable = false;
	rasterizerDesc.SlopeScaledDepthBias = 0.0f;

	// Create the rasterizer state from the description we just filled out.
	DX_SafeCall(mDxDevice->CreateRasterizerState(&rasterizerDesc, &mDxRasterizerState));

	// Now set the rasterizer state.
	mDxDeviceContext->RSSetState(mDxRasterizerState);
}

void RenderManager::shutdownDx()
{
#if BDE_GLOBAL_ENABLE_NICE_DESTROY
	mDxSwapChain->SetFullscreenState(false, NULL);

	mDxRasterizerState->Release(); mDxRasterizerState = NULL;
	mDxDepthStencilView->Release(); mDxDepthStencilView = 0;
	mDxDepthStencilState->Release(); mDxDepthStencilState = 0;
	mDxDepthStencilBuffer->Release(); mDxDepthStencilBuffer = 0;
	mDxRenderTargetView->Release(); mDxRenderTargetView = 0;
	mDxDeviceContext->Release(); mDxDeviceContext = 0;
	mDxDevice->Release(); mDxDevice = 0;
	mDxSwapChain->Release(); mDxSwapChain = 0;
#endif
}

void RenderManager::renderOneFrame()
{
	Assert(mDxDevice);
	Assert(mDxDeviceContext);
	FLOAT bgColor[4] = { 0.0f, 0.2f, 0.5f, 1.0f };
	mDxDeviceContext->ClearRenderTargetView(mDxRenderTargetView, bgColor);
	mDxDeviceContext->ClearDepthStencilView(mDxDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	for (int i = 0; i < mViewports.size(); ++i)
	{
		RenderViewport* vp = mViewports[i];
		vp->render();
	}

	// TODO add postProcess

	Assert(mDxSwapChain);
#if BDE_RENDER_ENABLE_VSYNC
	mDxSwapChain->Present(1, 0);
#else
	mDxSwapChain->Present(0, 0);
#endif
}

RenderVertexBuffer* RenderManager::createVertexBuffer()
{
	return RENDER_NEW(RenderVertexBuffer);
}
RenderIndexBuffer* RenderManager::createIndexBuffer()
{
	return RENDER_NEW(RenderIndexBuffer);
}
RenderMesh* RenderManager::createMesh(RenderIndexBuffer* indexBuf, RenderVertexBuffer* vertexBuf)
{
	return RENDER_NEW(RenderMesh)(indexBuf, vertexBuf);
}
RenderShader* RenderManager::createShader()
{
	return RENDER_NEW(RenderShader);
}
RenderMaterial* RenderManager::createMaterial(RenderShader* shader)
{
	return RENDER_NEW(RenderMaterial)(shader);
}
RenderViewport* RenderManager::createViewport()
{
	RenderViewport* vp = RENDER_NEW(RenderViewport);
	mViewports.append(vp);
	return vp;
}

void RenderManager::destroyVertexBuffer(RenderVertexBuffer*vb)
{
	RENDER_DELETE(vb, RenderVertexBuffer);
}
void RenderManager::destroyIndexBuffer(RenderIndexBuffer* ib)
{
	RENDER_DELETE(ib, RenderIndexBuffer);
}
void RenderManager::destroyMesh(RenderMesh* mesh)
{
	RENDER_DELETE(mesh, RenderMesh);
}
void RenderManager::destroyShader(RenderShader* shader)
{
	RENDER_DELETE(shader, RenderShader);
}
void RenderManager::destroyMaterial(RenderMaterial* mat)
{
	RENDER_DELETE(mat, RenderMaterial);
}
void RenderManager::destroyViewport(RenderViewport* vp)
{
	Assert(mViewports.eContains(vp));
	mViewports.eRemoveItem(vp);
	RENDER_DELETE(vp, RenderViewport);
}
