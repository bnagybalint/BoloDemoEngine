#pragma once

#include "Assist/Vector3.hpp"
#include "Assist/Quaternion.hpp"
#include "Assist/Transform.hpp"

#include <directxmath.h>

class RenderSceneElement
{
public:

	RenderSceneElement();
	virtual ~RenderSceneElement();

	void setWorldPosition(const Vector3& pos) { mWorldTransform.setPosition(pos); calculateCachedWorldMatrix(); }
	void setWorldOrientation(const Quaternion& ori) { mWorldTransform.setOrientation(ori); calculateCachedWorldMatrix(); }
	void setWorldScale(const Vector3& scale) { mWorldScale = scale; calculateCachedWorldMatrix(); }
	void setWorldTransform(const Transform& transform) { mWorldTransform = transform; calculateCachedWorldMatrix(); }

	const Transform& getWorldTransform() const { return mWorldTransform; }
	const Vector3& getWorldScale() const { return mWorldScale; }

	const DirectX::XMMATRIX& getDxWorldMatrix() const { return mCachedDxWorldMatrix; }
	const DirectX::XMVECTOR getDxPosition() const;

private:

	void calculateCachedWorldMatrix();

private:

	Transform mWorldTransform;
	Vector3 mWorldScale;

	DirectX::XMMATRIX mCachedDxWorldMatrix;

};

