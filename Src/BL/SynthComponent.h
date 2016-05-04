#pragma once

#include "Assist/Common.h"
#include "Assist/Vector2.h"
#include "Assist/Property.h"

#include "BL/SynthObject.h"

class GraphicsNode;
class GraphicsRectangle;
class GraphicsText;

class SynthComponent : public SynthObject
{
public:

	Property<Vector2> position;
	Property<Vector2> localAabbMin; // relative to position
	Property<Vector2> localAabbMax; // relative to position

public:

	SynthComponent(SynthScene* scene/*, AudioElement*/);
	~SynthComponent();

	bool performPick(const PickInput& input, /*out*/PickResult& result) override;

private:

	void onPropertyChanged(PropertyOwner* propOwner, PropertyBase* prop);

	void createRender();
	void destroyRender();

private:

	GraphicsNode* mRenderNode;
	GraphicsRectangle* mRenderRect;
	GraphicsText* mRenderText;
};

