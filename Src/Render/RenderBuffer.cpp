#include "RenderBuffer.h"

#include "Assist/Common.h"

#include "Render/RenderCommon.h"
#include "Render/RenderManager.h"
#include "Render/RenderShader.h"

#include <directxmath.h>
#include <d3d11.h>

// ================================================================================

struct RenderBufferVertexType
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 normal;
	DirectX::XMFLOAT3 tangent;
	DirectX::XMFLOAT2 texCoord;
};

// ================================================================================

RenderBuffer::RenderBuffer(D3D11_BIND_FLAG bindFlag)
	: mData(NULL)
	, mDataSize(0)
	, mBufferSize(0)
	, mDxBuffer(NULL)
	, mDxBufferBindFlag(bindFlag)
{
}

RenderBuffer::~RenderBuffer()
{
#if BDE_GLOBAL_ENABLE_NICE_DESTROY
	if (mDxBuffer)
		releaseBuffer();
#endif
}

void RenderBuffer::setData(void* data, unsigned int sizeInBytes)
{
	Assert(data);
	Assert(sizeInBytes > 0);
	if (!mDxBuffer)
	{
		// uninitialized buffer
		createBuffer(data, sizeInBytes);
	}
	else if (mBufferSize < sizeInBytes)
	{
		// there is not enough memory in the buffer to accommodate data

		releaseBuffer();
		createBuffer(data, sizeInBytes);
	}
	else
	{
		// there is enough memory in the buffer to accommodate data
		fillBuffer(data, sizeInBytes);
	}
}

void RenderBuffer::updateData(void* data, unsigned int sizeInBytes, unsigned int offsetInBytes)
{
	Assert(data);
	Assert(mDxBuffer); // maybe you should use setData?

	Assert(offsetInBytes < mDataSize);
	Assert(sizeInBytes <= mDataSize - offsetInBytes);

	Assert(mData);
	Memory::Memcopy(mData + offsetInBytes, data, sizeInBytes);

	// TODO this involves a second copy which could be optimized.
	// Possible solution: separate CPU and GPU data update methods
	fillBuffer(mData, mDataSize);
}

void RenderBuffer::createBuffer(void* data, unsigned int sizeInBytes)
{
	Assert(!mData);
	Assert(!mDxBuffer);
	
	mBufferSize = mDataSize = sizeInBytes;
	mData = new unsigned char[mBufferSize];

	Memory::Memcopy(mData, data, sizeInBytes);
#if BDE_RENDER_DX_DEBUG
	Memory::Memset(mData + mDataSize, 0xCD, mBufferSize - mDataSize);
#endif

	D3D11_SUBRESOURCE_DATA resourceData;
	Memory::Memzero(&resourceData, sizeof(D3D11_SUBRESOURCE_DATA));
	resourceData.pSysMem = data;
	resourceData.SysMemPitch = 0;
	resourceData.SysMemSlicePitch = 0;

	D3D11_BUFFER_DESC bufferDesc;
	Memory::Memzero(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags = mDxBufferBindFlag;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.ByteWidth = mBufferSize;

	DX_GetDevice(dxdev);
	DX_SafeCall(dxdev->CreateBuffer(&bufferDesc, &resourceData, &mDxBuffer));
}

void RenderBuffer::fillBuffer(void* data, unsigned int sizeInBytes)
{
	Assert(mData);
	Assert(mDxBuffer);

	mDataSize = sizeInBytes;
	Memory::Memcopy(mData, data, sizeInBytes);
#if BDE_RENDER_DX_DEBUG
	// fill rest with rubbish
	Memory::Memset(mData + mDataSize, 0xCD, mBufferSize - mDataSize);
#endif

	DX_GetDeviceContext(dxctx);
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	DX_SafeCall(dxctx->Map(mDxBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource));
	Memory::Memcopy(mappedResource.pData, data, mDataSize);
	dxctx->Unmap(mDxBuffer, 0);
}

void RenderBuffer::releaseBuffer()
{
	Assert(mData);
	delete[] mData; mData = NULL;
	Assert(mDxBuffer);
	mDxBuffer->Release(); mDxBuffer = NULL;
}
// ================================================================================

RenderIndexBuffer::RenderIndexBuffer()
	: RenderBuffer(D3D11_BIND_INDEX_BUFFER)
	, mIndexCount(0)
{
}

RenderIndexBuffer::~RenderIndexBuffer()
{
#if BDE_GLOBAL_ENABLE_NICE_DESTROY
#endif
}

void RenderIndexBuffer::bind()
{
	DX_GetDeviceContext(dxctx);
	dxctx->IASetIndexBuffer(getDxBuffer(), DXGI_FORMAT_R32_UINT, 0);
	dxctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void RenderIndexBuffer::draw()
{
	Assert(mIndexCount > 0);
	DX_GetDeviceContext(dxctx); 
	dxctx->DrawIndexed(mIndexCount, 0, 0);
}

void RenderIndexBuffer::setIndexData(IndexType* indices, unsigned int indexCount)
{
	RenderBuffer::setData(indices, indexCount*sizeof(IndexType));
	mIndexCount = indexCount;
}

// ================================================================================

RenderVertexBuffer::RenderVertexBuffer()
	: RenderBuffer(D3D11_BIND_VERTEX_BUFFER)
	, mDxPolygonLayout(NULL)
	, mBoundShader(NULL)
{
}

RenderVertexBuffer::~RenderVertexBuffer()
{
#if BDE_GLOBAL_ENABLE_NICE_DESTROY
#endif
}

void RenderVertexBuffer::bind(RenderShader* shader)
{
	DX_GetDeviceContext(dxctx);

	bindShader(shader);
	
	unsigned int  stride = sizeof(RenderBufferVertexType);
	unsigned int  offset = 0;
	ID3D11Buffer* bufs   = getDxBuffer();
	dxctx->IASetVertexBuffers(0, 1, &bufs, &stride, &offset);
}

#define DX_VerteBufffer_PolygonLayout(layout,id,semanticName,semanticIndex,format,slot,slotClass,byteOffset) \
	{ \
		layout[id].SemanticName = semanticName; \
		layout[id].SemanticIndex = semanticIndex; \
		layout[id].Format = format; \
		layout[id].InputSlot = slot; \
		layout[id].InputSlotClass = slotClass; \
		layout[id].AlignedByteOffset = byteOffset; \
		layout[id].InstanceDataStepRate = 0; \
	}
void RenderVertexBuffer::bindShader(RenderShader* shader)
{
	Assert(shader);
	if (mBoundShader != shader)
	{
		if (mDxPolygonLayout)
		{
			mDxPolygonLayout->Release();
			mDxPolygonLayout = NULL;
		}

		Memory::Memzero(&mDxPolygonLayoutDesc, msNumVertexLayoutComponents*sizeof(D3D11_INPUT_ELEMENT_DESC));
		DX_VerteBufffer_PolygonLayout(mDxPolygonLayoutDesc, 0, "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_INPUT_PER_VERTEX_DATA, 0);
		DX_VerteBufffer_PolygonLayout(mDxPolygonLayoutDesc, 1, "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_INPUT_PER_VERTEX_DATA, D3D11_APPEND_ALIGNED_ELEMENT);
		DX_VerteBufffer_PolygonLayout(mDxPolygonLayoutDesc, 2, "TANGENT",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_INPUT_PER_VERTEX_DATA, D3D11_APPEND_ALIGNED_ELEMENT);
		DX_VerteBufffer_PolygonLayout(mDxPolygonLayoutDesc, 3, "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_INPUT_PER_VERTEX_DATA, D3D11_APPEND_ALIGNED_ELEMENT);

		DX_GetDevice(dxdev);
		DX_SafeCall(dxdev->CreateInputLayout(mDxPolygonLayoutDesc, msNumVertexLayoutComponents, shader->getVertexShaderBuffer(), shader->getVertexShaderBufferSize(), &mDxPolygonLayout));

		mBoundShader = shader;
	}

	Assert(mDxPolygonLayout);

	DX_GetDeviceContext(dxctx);
	dxctx->IASetInputLayout(mDxPolygonLayout);
}

void RenderVertexBuffer::setVertexData(RenderBufferVertexType* vertices, unsigned int vertexCount)
{
	RenderBuffer::setData(vertices, vertexCount*sizeof(RenderBufferVertexType));
}

// ================================================================================

RenderConstantBuffer::RenderConstantBuffer() 
	:RenderBuffer(D3D11_BIND_CONSTANT_BUFFER)
{
}

RenderConstantBuffer::~RenderConstantBuffer()
{
#if BDE_GLOBAL_ENABLE_NICE_DESTROY
#endif
}

void RenderConstantBuffer::bind(int bufferSlot)
{
	DX_GetDeviceContext(dxctx);

	ID3D11Buffer* buf = getDxBuffer();
	dxctx->VSSetConstantBuffers(bufferSlot, 1, &buf);
	dxctx->PSSetConstantBuffers(bufferSlot, 1, &buf);
}