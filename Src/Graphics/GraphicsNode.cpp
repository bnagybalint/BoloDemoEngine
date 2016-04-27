#include "GraphicsNode.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <d2d1.h>
#include <d2d1helper.h>

#include "Graphics/GraphicsObject.h"
#include "Graphics/GraphicsCanvas.h"
#include "Graphics/GraphicsConverter.h"

GraphicsNode::GraphicsNode()
	: mParentNode(NULL)
	, mChildNodes()
	, mObjects()
{
}

GraphicsNode::~GraphicsNode()
{
	Assert(mChildNodes.isEmpty());
	mChildNodes.clear();
	Assert(mObjects.isEmpty());
	mObjects.clear();
}

void GraphicsNode::addObject(GraphicsObject* object)
{
	mObjects.append(object);
}

void GraphicsNode::removeObject(GraphicsObject* object)
{
	mObjects.eRemoveItem(object);
}

void GraphicsNode::draw(GraphicsCanvas* target)
{
	sortObjects();
	drawObjects(target);

	for (int i = 0; i < mChildNodes.size(); ++i)
		mChildNodes[i]->draw(target);
}

void GraphicsNode::sortObjects()
{
	// TODO
}

void GraphicsNode::drawObjects(GraphicsCanvas* target)
{
	Vector2 pos;
	float   rot;
	getWorldTransform(pos, rot);

	target->setModelTransform(pos, rot);
	for (int i = 0; i < mObjects.size(); ++i)
		mObjects[i]->draw(target);
}

void GraphicsNode::reparent(GraphicsNode* newParentNode)
{
	if (mParentNode)
		mParentNode->removeChildNode(this);
	if (newParentNode)
		newParentNode->addChildNode(this);
}

void GraphicsNode::addChildNode(GraphicsNode* node)
{
	Assert(node);
	Assert(!node->mParentNode);
	Assert(!mChildNodes.eContains(node));

	mChildNodes.append(node);
	node->mParentNode = this;
}

void GraphicsNode::removeChildNode(GraphicsNode* node)
{
	Assert(node);
	Assert(node->mParentNode == this);
	Assert(mChildNodes.eContains(node)); // sanity check

	node->mParentNode = NULL;
	mChildNodes.eRemoveItem(node);
}

void GraphicsNode::getWorldTransform(/*out*/Vector2& position, /*out*/float& rotation) const
{
	Vector2 pPos = Vector2::ZERO;
	float   pRot = 0.0f;
	if (mParentNode)
		mParentNode->getWorldTransform(pPos, pRot);

	position = pPos + mPosition.rotated(pRot);
	rotation = pRot + mRotation;
}


