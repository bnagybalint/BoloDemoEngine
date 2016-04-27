#pragma once

#include "Assist/Common.h"
#include "Assist/Array.h"

class GeometryGenerator
{
public:

	// Create a UV sphere with unit radius and "axis" pointing in the Y direction.
	// Tessellation in the XZ plane is started from the +Z axis, spinning around axis +Y.
	// Tangents are horizontal, 
	static void generateSphere(
		int stacks, // Number of vertical quad rows.
		int slices, // Number of horizontal quad columns.
		/*out*/Array<unsigned int>& outIndices, /*out*/Array<float>& outVertices);

private:

	GeometryGenerator();
	~GeometryGenerator();
};

