#include "RenderMesh.h"

#include "Assist/Common.h"

#include "Render/RenderBuffer.h"
#include "Render/RenderManager.h"
#include "Render/RenderMaterial.h"


RenderMesh::RenderMesh(RenderIndexBuffer* indexBuffer, RenderVertexBuffer* vertexBuffer)
	:mIndexBuffer(indexBuffer), mVertexBuffer(vertexBuffer)
{
	Assert(mIndexBuffer);
	Assert(mVertexBuffer);
}

RenderMesh::~RenderMesh()
{
#if BDE_GLOBAL_ENABLE_NICE_DESTROY
#endif
}

void RenderMesh::setupForRendering(RenderMaterial* material)
{
	mIndexBuffer->bind();
	mVertexBuffer->bind(material->getShader());
}

void RenderMesh::render()
{
	mIndexBuffer->draw();
}
