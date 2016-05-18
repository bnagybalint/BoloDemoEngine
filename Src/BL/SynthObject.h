#pragma once

#include "Assist/Common.h"
#include "Assist/PropertyOwner.h"

#include "BL/IPickable2D.h"

class SynthScene;

class SynthObject 
	: public PropertyOwner
	, public IPickable2D
{
public:

	SynthObject(SynthScene* scene, const String& name);
	DISABLE_COPY(SynthObject);
	~SynthObject();

	SynthScene* getScene() const { return mScene; }
	const String& getName() const { return mName; }

protected:

	SynthScene* mScene;

	String mName;
};

