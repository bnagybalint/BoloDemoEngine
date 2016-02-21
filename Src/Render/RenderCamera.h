#pragma once

#include "Render/RenderSceneElement.h"

#include <directxmath.h>

class RenderCamera : public RenderSceneElement
{
	// Forward direction is local +z
	// Up direction is local +y

public:
	RenderCamera();
	~RenderCamera();

	DirectX::XMMATRIX getDxViewMatrix() const; //calculated every time

private:

	// -----------------------------
	// extended functionality
public:
	void setCameraAxes(const Vector3& dir, const Vector3& up);

	void roll(float angleRad);
	void pitch(float angleRad);
	void yaw(float angleRad);
	void calculateBasis();

	Vector3 getRight() const;

private:
	Vector3 mUpVector;
	Vector3 mDirection;
	// -----------------------------
};

