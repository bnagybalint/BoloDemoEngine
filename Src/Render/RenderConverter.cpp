#include "RenderConverter.h"

#include "Assist/Vector3.hpp"
#include "Assist/Quaternion.hpp"
#include "Assist/Matrix3x3.hpp"
#include "Assist/Matrix4x4.hpp"
#include "Assist/Color.h" 

#include <directxmath.h>

/*static*/ DirectX::XMVECTOR RenderConverter::convertToDX(const Vector3& v) {
	DirectX::XMVECTOR rv;
	float* rvptr = reinterpret_cast<float*>(&rv);
	rvptr[0] = v.x;
	rvptr[1] = v.y;
	rvptr[2] = v.z;
	rvptr[3] = v.w;
	return rv;
}

/*static*/ DirectX::XMVECTOR RenderConverter::convertToDX(const Quaternion& q) {
	DirectX::XMVECTOR rv;
	float* rvptr = reinterpret_cast<float*>(&rv);
	rvptr[0] = q.x;
	rvptr[1] = q.y;
	rvptr[2] = q.z;
	rvptr[3] = q.w;
	return rv;
}

/*static*/ DirectX::XMMATRIX RenderConverter::convertToDX(const Matrix3x3& matrix) {
	DirectX::XMMATRIX rv;
	float* rvptr = reinterpret_cast<float*>(&rv.r[0]);
	rvptr[0] = matrix.mx[0];
	rvptr[1] = matrix.mx[1];
	rvptr[2] = matrix.mx[2];
	rvptr[3] = 0.0f;
	rvptr[4] = matrix.mx[3];
	rvptr[5] = matrix.mx[4];
	rvptr[6] = matrix.mx[5];
	rvptr[7] = 0.0f;
	rvptr[8] = matrix.mx[6];
	rvptr[9] = matrix.mx[7];
	rvptr[10] = matrix.mx[8];
	rvptr[11] = 0.0f;
	rvptr[12] = 0.0f;
	rvptr[13] = 0.0f;
	rvptr[14] = 0.0f;
	rvptr[15] = 1.0f;
	return rv;
}

/*static*/ DirectX::XMMATRIX RenderConverter::convertToDX(const Matrix4x4& matrix) {
	DirectX::XMMATRIX rv;
	float* rvptr = reinterpret_cast<float*>(&rv.r[0]);
	for (int i = 0; i < 16; i++)
		rvptr[i] = matrix.mx[i];
	return rv;
}

/*static*/ DirectX::XMVECTOR RenderConverter::convertToDX(const Color& c)
{
	DirectX::XMVECTOR rv;
	float* rvptr = reinterpret_cast<float*>(&rv);
	rvptr[0] = c.r;
	rvptr[1] = c.g;
	rvptr[2] = c.b;
	rvptr[3] = c.a;
	return rv;
}

/*static*/ uint32 RenderConverter::toPackedColor(const Vector3& color)
{
	(void)color;
	Unimplemented(); // TODO implement
	return 0;
}

/*static*/ uint32 RenderConverter::toPackedColor(float r, float g, float b, float a)
{
	(void)r;
	(void)g;
	(void)b;
	(void)a;
	Unimplemented(); // TODO implement
	return 0;
}

/*static*/ uint32 RenderConverter::toPackedColor(uint8 r, uint8 g, uint8 b, uint8 a)
{
	return uint32(r) | uint32(g) << 8 | uint32(b) << 16 | uint32(a) << 24;
}

