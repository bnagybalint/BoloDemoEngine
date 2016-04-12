#pragma once

#include "Assist/Common.h"
#include "Assist/Array.h"

class GraphicsElement;
class GraphicsElementContext;
class GraphicsCanvas;

class GraphicsObject
{
private:

	friend class GraphicsCanvas;

public:

	void draw();

	GraphicsElementContext* getContext() { return mContext; }

private:

	GraphicsObject(GraphicsCanvas* canvas);
	DISABLE_COPY(GraphicsObject);
	virtual ~GraphicsObject();

private:

	void sortElements();

private:

	GraphicsCanvas*         mCanvas;
	GraphicsElementContext* mContext;
	Array<GraphicsElement*> mElements;
};

