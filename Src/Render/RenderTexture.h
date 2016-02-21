#pragma once

#include "Render/RenderCommon.h"

struct ID3D11Texture2D;
struct ID3D11ShaderResourceView;

class RenderTexture
{

public:
	RenderTexture();
	~RenderTexture();

	void setData(uint32* dataRGBA32, unsigned int height, unsigned int width);

	void bindToShader(unsigned int resourceIndex);

private:

	void createTexture(uint32* dataRGBA32, unsigned int height, unsigned int width);
	void fillTexture(uint32* dataRGBA32);
	void releaseTexture();

private:

	uint32*      mData;
	unsigned int mDataHeight;
	unsigned int mDataWidth;

	ID3D11Texture2D* mDxTexture;
	ID3D11ShaderResourceView* mDxTextureView;

};

