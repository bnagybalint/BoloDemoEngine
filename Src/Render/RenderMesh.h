#pragma once

class RenderIndexBuffer;
class RenderVertexBuffer;
class RenderMaterial;

class RenderMesh
{
public:
	RenderMesh(RenderIndexBuffer* indexBuffer, RenderVertexBuffer* vertexBuffer);
	~RenderMesh();

	void setupForRendering(RenderMaterial* material);
	void render();

private:

	RenderIndexBuffer* mIndexBuffer;
	RenderVertexBuffer* mVertexBuffer;
};

