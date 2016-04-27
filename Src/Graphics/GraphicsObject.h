#pragma once

#include "Assist/Common.h"
#include "Assist/Array.h"

class GraphicsCanvas;

class GraphicsObject
{
public:

	GraphicsObject();
	DISABLE_COPY(GraphicsObject);
	virtual ~GraphicsObject();

	void draw(GraphicsCanvas* target);

	// TODO getset Position -> local, relative to node
	// TODO getset Rotation -> local, relative to node

private:

	virtual void drawImpl(GraphicsCanvas* target) = 0;

	// called first time the object is drawn on a canvas
	// purpose: create device-dependent resources for the object
	virtual void createResourcesImpl(GraphicsCanvas* target) = 0;
	virtual void destroyResourcesImpl(GraphicsCanvas* target) = 0;

private:

	// TODO this solution is not nice, should be able to switch 
	// between canvases real quick, without destroying-and-creating resources.
	GraphicsCanvas* mCurrectCanvas;
};

