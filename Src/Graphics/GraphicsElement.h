#pragma once

#include "Assist/Common.h"
#include "Assist/Vector2.h"

class GraphicsElementContext;

class GraphicsElement
{
public:

	GraphicsElement();
	virtual ~GraphicsElement();

	virtual void drawElement(GraphicsElementContext* context) = 0;

	const Vector2& getLocalPosition() const { return mLocalPosition; }
	void setLocalPosition(const Vector2& val) { mLocalPosition = val; }

	float getLocalOrientation() const { return mLocalOrientation; }
	void setLocalOrientation(float val) { mLocalOrientation = val; }

	int getZOrder() const { return mZOrder; }
	void setZOrder(int val) { mZOrder = val; }

private:

	Vector2 mLocalPosition;
	float mLocalOrientation;

	int mZOrder;
};

