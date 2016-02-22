#pragma once

#include "Assist/Common.h"

class Render2DRenderTarget;

class Render2DRenderElement
{
public:

	virtual void render(Render2DRenderTarget* renderTarget) = 0;

	void setZOrder(int z) { mZOrder = z; }
	int  getZOrder() const { return mZOrder; }

protected:

	Render2DRenderElement();
	~Render2DRenderElement();

private:

	int mZOrder;
};

