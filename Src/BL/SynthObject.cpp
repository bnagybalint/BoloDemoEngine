#include "SynthObject.h"


SynthObject::SynthObject(SynthScene* scene, const String& name)
	: PropertyOwner()
	, IPickable2D(this)
	, mScene(scene)
	, mName(name)
{
}

SynthObject::~SynthObject()
{
}
