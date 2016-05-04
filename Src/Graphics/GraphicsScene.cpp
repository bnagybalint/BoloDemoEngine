#include "GraphicsScene.h"

#include "Graphics/GraphicsNode.h"

GraphicsScene::GraphicsScene()
	: mRootNodes()
{
}

GraphicsScene::~GraphicsScene()
{
	Unimplemented();
	// TODO
}

void GraphicsScene::draw(GraphicsCanvas* target)
{
	for (int i = 0; i < mRootNodes.size(); ++i)
		mRootNodes[i]->draw(target);
}

void GraphicsScene::addNode(GraphicsNode* node, GraphicsNode* parentNode)
{
	Assert(node);

	if (parentNode)
		parentNode->addChildNode(node);
	else
		mRootNodes.append(node);
}

void GraphicsScene::removeNode(GraphicsNode* node)
{
	Assert(node);
	Unimplemented();
}
