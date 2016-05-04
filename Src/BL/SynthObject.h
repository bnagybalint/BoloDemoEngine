#pragma once

#include "Assist/Common.h"
#include "Assist/PropertyOwner.h"

#include "BL/IPickable.h"

class SynthScene;

class SynthObject 
	: public PropertyOwner
	, public IPickable2D
{
public:

	SynthObject(SynthScene* scene);
	DISABLE_COPY(SynthObject);
	~SynthObject();
	
protected:

	SynthScene* mScene;
};

