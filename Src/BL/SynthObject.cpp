#include "SynthObject.h"


SynthObject::SynthObject(SynthScene* scene)
	: PropertyOwner()
	, IPickable2D()
	, mScene(scene)
{
}

SynthObject::~SynthObject()
{
}
