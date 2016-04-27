#pragma once

#include "Assist/Common.h"
#include "Assist/Array.h"

class GraphicsNode;
class GraphicsObject;
class GraphicsCanvas;

class GraphicsScene
{
public:

	GraphicsScene();
	DISABLE_COPY(GraphicsScene);
	~GraphicsScene();

	void draw(GraphicsCanvas* target);

	// Add node to scene. This is the desired way of adding a node to scene,
	// not by using Node::addChildNode() or Node::reparent()
	// Note: life-cycle is managed by the creating party.
	void addNode(GraphicsNode* node, GraphicsNode* parentNode);

private:

	Array<GraphicsNode*> mRootNodes;
};

