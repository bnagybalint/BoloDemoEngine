#include "GraphicsObject.h"

#include "Graphics/GraphicsElementContext.h"
#include "Graphics/GraphicsElement.h"


GraphicsObject::GraphicsObject(GraphicsCanvas* canvas)
	: mCanvas(canvas)
	, mContext(NULL)
	, mElements()
{
	mContext = new GraphicsElementContext(mCanvas);
}

GraphicsObject::~GraphicsObject()
{
	delete mContext; mContext = NULL;
}

void GraphicsObject::draw()
{
	for (int i = 0; i < mElements.size(); i++)
	{
		GraphicsElement* element = mElements[i];
		element->drawElement(mContext);
	}
}

void GraphicsObject::sortElements()
{
	Unimplemented();
}