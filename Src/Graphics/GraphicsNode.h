#pragma once

#include "Assist/Common.h"
#include "Assist/Array.h"
#include "Assist/Vector2.h"

class GraphicsObject;
class GraphicsCanvas;

class GraphicsNode
{
public:

	GraphicsNode();
	DISABLE_COPY(GraphicsNode);
	virtual ~GraphicsNode();

	void addObject(GraphicsObject* object);
	void removeObject(GraphicsObject* object);

	void draw(GraphicsCanvas* target);

	void reparent(GraphicsNode* newParentNode);
	void addChildNode(GraphicsNode* node);
	void removeChildNode(GraphicsNode* node);

	const Vector2& getPosition() const { return mPosition; }
	void setPosition(const Vector2& val) { mPosition = val; }

	float getRotation() const { return mRotation; }
	void setRotation(float val) { mRotation = val; }

	void getWorldTransform(/*out*/Vector2& position, /*out*/float& rotation) const;

private:

	void sortObjects();
	void drawObjects(GraphicsCanvas* target);

private:

	GraphicsNode* mParentNode;
	Array<GraphicsNode*> mChildNodes;
	Array<GraphicsObject*> mObjects;

	Vector2 mPosition;
	float mRotation; // in radians
};

