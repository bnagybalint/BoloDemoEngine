#pragma once

#include "Render/RenderSceneElement.h"

#include <directxmath.h>

class RenderLightSource : public RenderSceneElement
{
public:
	RenderLightSource();
	~RenderLightSource();

	void lookAt(const Vector3& center, const Vector3& up = Vector3::UNIT_Y);

	void setColor(const Vector3& color);

	const DirectX::XMVECTOR getDxDirection() const;
	const DirectX::XMVECTOR& getDxColor() const { return mDxLightColor; }

private:

	DirectX::XMVECTOR mDxLightColor;
};

