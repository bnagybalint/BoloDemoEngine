#pragma once

#include "Render/RenderCommon.h"

#include <d3d11.h>

struct ID3D11Buffer;

class RenderShader;

class RenderBuffer
{
public:

	virtual ~RenderBuffer();

	// Set data inside the buffer
	// WARNING: might need to resize the buffer
	void setData(void* data, unsigned int sizeInBytes);

	// Overwrite part of the buffer
	// WARNING: must be populated with data already (setData called)
	void updateData(void* data, unsigned int sizeInBytes, unsigned int offsetInBytes);

protected:

	RenderBuffer(D3D11_BIND_FLAG bindFlag);

	// WARNING: pointer might change upon buffer resize
	ID3D11Buffer* getDxBuffer() const { return mDxBuffer; }

private:

	void createBuffer(void* data, unsigned int sizeInBytes);
	void fillBuffer(void* data, unsigned int sizeInBytes);
	void releaseBuffer();

private:

	unsigned char* mData;
	unsigned int mDataSize; // in bytes
	unsigned int mBufferSize; // in bytes

	ID3D11Buffer*     mDxBuffer;
	UINT              mDxBufferBindFlag;
};

// ================================================================================

class RenderIndexBuffer : public RenderBuffer
{
public:

	typedef unsigned int IndexType;

public:

	RenderIndexBuffer();
	~RenderIndexBuffer();

	void bind();
	void draw();

	void setIndexData(IndexType* indices, unsigned int indexCount);

private:

	using RenderBuffer::setData; // hide

private:

	unsigned int mIndexCount;
};

// ================================================================================

struct RenderBufferVertexType;

class RenderVertexBuffer : public RenderBuffer
{
public:

	static const unsigned int msNumVertexLayoutComponents = 4;

public:

	RenderVertexBuffer();
	~RenderVertexBuffer();

	void bind(RenderShader* shader);

	void setVertexData(RenderBufferVertexType* vertices, unsigned int vertexCount);

private:

	using RenderBuffer::setData; // hide

private:

	void bindShader(RenderShader* shader);

private:

	D3D11_INPUT_ELEMENT_DESC mDxPolygonLayoutDesc[msNumVertexLayoutComponents];
	ID3D11InputLayout*       mDxPolygonLayout;

	// last shader used to render this buffer. used to optimize input layout creation
	// TODO this caching should be solved in a nicer way
	RenderShader*            mBoundShader;

};

// ================================================================================

class RenderConstantBuffer : public RenderBuffer
{
public:

	RenderConstantBuffer();
	~RenderConstantBuffer();

	void bind(int bufferSlot);
};


