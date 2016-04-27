#pragma once

#include "Assist/Common.h"
#include "Assist/Vector3.hpp"
#include "Assist/Vector2.h"
#include "Assist/Array.h"

struct MeshVertex {
	Vector3 position;
	Vector3 normal;
	Vector3 tangent;
	Vector2 texCoord;

	static const int OffsetPosition = 0;
	static const int OffsetNormal   = 3;
	static const int OffsetTangent  = 6;
	static const int OffsetTexCoord = 9;
	static const int NumComponents  = 11;
};

struct Mesh
{
public:

	Mesh();
	DISABLE_COPY(Mesh);
	~Mesh();

	int getVertexCount() const { return mVertexData.size() / MeshVertex::NumComponents; }
	int getIndexCount() const { return mIndexData.size(); }

	const Array<float>& getVertexData() const { return mVertexData; }
	Array<float>& getVertexData() { return mVertexData; }
	const Array<unsigned int>& getIndexData() const { return mIndexData; }
	Array<unsigned int>& getIndexData() { return mIndexData; }

public:

	Array<float> mVertexData;
	Array<unsigned int> mIndexData;
};

