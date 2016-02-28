#pragma once

#include "Assist/Common.h"
#include "Assist/Vector2.h"
#include "Assist/Color.h"

class Render2DRenderTarget;

class Render2DRenderElement
{
public:

	virtual void render(Render2DRenderTarget* renderTarget) = 0;

	float getRotation() const { return mRotation; }
	void setRotation(float rot) { mRotation = rot; }

	const Vector2& getPosition() const { return mPosition; }
	void setPosition(const Vector2& pos) { mPosition = pos; }

	int  getZOrder() const { return mZOrder; }
	void setZOrder(int z) { mZOrder = z; }

	const Color& getLineColor() const { return mLineColor; }
	void setLineColor(const Color& val) { mLineColor = val; }

	const Color& getFillColor() const { return mFillColor; }
	void setFillColor(const Color& val) { mFillColor = val; }

protected:

	Render2DRenderElement();
	~Render2DRenderElement();

private:

	Vector2 mPosition;
	float   mRotation; // Rotation angle radians, counting from +x, CCW
	int     mZOrder;   // Render order: lowest z value first

	Color   mLineColor;
	Color   mFillColor;
};

