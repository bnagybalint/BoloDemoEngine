#include "GraphicsObject.h"

#include "Graphics/GraphicsCanvas.h"


GraphicsObject::GraphicsObject()
	: mCurrectCanvas(NULL)
{
}

GraphicsObject::~GraphicsObject()
{
}

void GraphicsObject::draw(GraphicsCanvas* target)
{
	if (mCurrectCanvas != target)
	{
		if (mCurrectCanvas)
			destroyResourcesImpl(target);

		createResourcesImpl(target);
		mCurrectCanvas = target;
	}
	
	drawImpl(mCurrectCanvas);
}
