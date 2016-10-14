#pragma once

#include "Assist/Common.h"

#include "Assist/Vector3.hpp"
#include "Assist/Quaternion.hpp"
#include "Assist/Transform.hpp"

#include <directxmath.h>

class RenderScene;

class RenderSceneElement
{
public:

	RenderSceneElement(RenderScene* scene);
	virtual ~RenderSceneElement();

	void setWorldPosition(const Vector3& pos) { mWorldTransform.setPosition(pos); }
	void setWorldOrientation(const Quaternion& ori) { mWorldTransform.setOrientation(ori); }
	void setWorldScale(const Vector3& scale) { mWorldScale = scale; }
	void setWorldTransform(const Transform& transform) { mWorldTransform = transform; }

	const Transform& getWorldTransform() const { return mWorldTransform; }
	const Vector3& getWorldScale() const { return mWorldScale; }

	RenderScene* getScene() { return mScene; }

	DirectX::XMMATRIX getDxWorldMatrix() const;
	DirectX::XMVECTOR getDxPosition() const;

private:

	RenderScene* mScene;

	Transform mWorldTransform;
	Vector3 mWorldScale;
};

