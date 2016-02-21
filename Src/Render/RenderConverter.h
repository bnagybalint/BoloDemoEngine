#pragma once

#include "Assist/Common.h"

#include "Render/RenderCommon.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <directxmath.h>

class Vector3;
class Quaternion;
class Matrix3x3;
class Matrix4x4;

struct RenderConverter
{
	static DirectX::XMVECTOR convertToDX(const Vector3& v);
	static DirectX::XMVECTOR convertToDX(const Quaternion& q);
	static DirectX::XMMATRIX convertToDX(const Matrix3x3& matrix);
	static DirectX::XMMATRIX convertToDX(const Matrix4x4& matrix);

	static uint32 toPackedColor(const Vector3& color);               // rgba = [0,1]
	static uint32 toPackedColor(float r, float g, float b, float a); // rgba = [0,1]
	static uint32 toPackedColor(uint8 r, uint8 g, uint8 b, uint8 a); // rgba = [0,255]
};
