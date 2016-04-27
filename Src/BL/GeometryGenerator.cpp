#include "GeometryGenerator.h"

#include "Assist/MathCommon.h"

#include "BL/Mesh.h"

void GeometryGenerator::generateSphere(
	int stacks, int slices, 
	/*out*/Array<unsigned int>& outIndices, /*out*/Array<float>& outVertices)
{
	Assert(stacks > 1);
	Assert(slices > 2);

#if BDE_BL_ARRAY_PREALLOCATION
	outIndices.reserve(stacks*slices * (2*3));
	outVertices.reserve(stacks*slices * MeshVertex::NumComponents);
#endif


	const int ni = slices;
	const int nj = stacks - 1;
	
	const float uden = float(slices);
	const float vden = float(stacks);

	int previ = slices - 1;
	for (int i = 0; i < slices; ++i)
	{
		float u = float(i) / uden;
		float a = u * Math::B_2PI;
		float cosa = Math::Cos(a);
		float sina = Math::Sin(a);
		
		int prevj = 0;
		for (int j = 1; j < stacks; ++j)
		{
			float v = float(j) / vden;
			float b = v * Math::B_PI;
			float cosb = Math::Cos(b);
			float sinb = Math::Sin(b);

			float x = sinb * sina;
			float y = cosb;
			float z = sinb * cosa;

			// position
			outVertices.append(x); outVertices.append(y); outVertices.append(z);
			// normal
			outVertices.append(x); outVertices.append(y); outVertices.append(z);
			// tangent
			outVertices.append(-z); outVertices.append(0.0f); outVertices.append(x);
			// texcoord
			outVertices.append(u); outVertices.append(1.0f - v);

			if (j > 1) // not the first full row (counting from top)
			{
				// previ    i
				//     +----+ prevj
				//     |   /|
				//     |  / |
				//     | /  |
				//     |/   |
				//     +----+ j

				outIndices.append(previ*nj + prevj - 1);
				outIndices.append(previ*nj +     j - 1);
				outIndices.append(    i*nj + prevj - 1);

				outIndices.append(previ*nj +     j - 1);
				outIndices.append(    i*nj +     j - 1);
				outIndices.append(    i*nj + prevj - 1);
			}

			prevj = j;
		}
		previ = i;
	}

	int idxtop = ni*nj;
	int idxbot = idxtop + 1;

	// Top
	outVertices.append(0.0f); outVertices.append(1.0f); outVertices.append(0.0f);
	outVertices.append(0.0f); outVertices.append(1.0f); outVertices.append(0.0f);
	outVertices.append(0.0f); outVertices.append(0.0f); outVertices.append(0.0f);
	outVertices.append(0.0f); outVertices.append(1.0f);

	// Bottom
	outVertices.append(0.0f); outVertices.append(-1.0f); outVertices.append(0.0f);
	outVertices.append(0.0f); outVertices.append(-1.0f); outVertices.append(0.0f);
	outVertices.append(0.0f); outVertices.append(0.0f);  outVertices.append(0.0f);
	outVertices.append(0.0f); outVertices.append(0.0f);

	previ = slices - 1;
	for (int i = 0; i < slices; ++i)
	{
		//          + idxtop
		//         /|
		//        / |
		//       /  |
		//      /   |
		//     +----+ 0
		// previ	i

		outIndices.append(idxtop);
		outIndices.append(previ*nj + 0);
		outIndices.append(    i*nj + 0);

		// previ    i
		//     +----+
		//     |   /
		//     |  / 
		//     | /  
		//     |/   
		//     +
		//     idxbot

		outIndices.append(    i*nj + nj - 1);
		outIndices.append(previ*nj + nj - 1);
		outIndices.append(idxbot);

		previ = i;
	}
}