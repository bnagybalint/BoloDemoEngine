#pragma once

#include "Assist/Common.h"
#include "Assist/Vector2.h"
#include "Assist/Property.h"

#include "BL/SynthObject.h"
#include "BL/Picker2D.h"

class GraphicsNode;
class GraphicsRectangle;
class GraphicsText;

class AudioComponent;

class SynthComponent : public SynthObject
{
public:

	Property<Vector2> position;
	Property<Vector2> localAabbMin; // relative to position
	Property<Vector2> localAabbMax; // relative to position

public:

	SynthComponent(SynthScene* scene, const String& name, AudioComponent* audioComponent);
	~SynthComponent();

	// Inherited from IPickable2D
	bool performPick(const Picker2D::PickInput& input, /*out*/Picker2D::PickResult& result) override;

private:

	void onPropertyChanged(PropertyOwner* propOwner, PropertyBase* prop);

	void createRender();
	void destroyRender();

private:

	AudioComponent* mAudioComponent;

	GraphicsNode* mRenderNode;
	GraphicsRectangle* mRenderRect;
	GraphicsText* mRenderText;
};

