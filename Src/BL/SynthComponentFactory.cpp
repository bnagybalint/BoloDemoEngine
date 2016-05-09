#include "SynthComponentFactory.h"

#include "BL/SynthScene.h"
#include "BL/SynthComponent.h"

#include "Audio/AudioComponent.h"
#include "Audio/AudioOscillator.h"
#include "Audio/AudioOutput.h"
#include "Audio/AudioBiquadFilter.h"

#include "Assist/NameGenerator.h"

DEFINE_SINGLETON_IMPL(SynthComponentFactory);

/*static*/const char* SynthComponentFactory::TYPENAME_OSCILLATOR = "oscillator";
/*static*/const char* SynthComponentFactory::TYPENAME_BIQUAD     = "biquad";
/*static*/const char* SynthComponentFactory::TYPENAME_OUTPUT     = "output";

SynthComponentFactory::SynthComponentFactory()
{
}

SynthComponentFactory::~SynthComponentFactory()
{
}

SynthComponent* SynthComponentFactory::createSynthComponent(const String& typeName, SynthScene* scene)
{
	AudioComponent* ac = NULL;
	String name = NameGenerator::getInstance()->generateName(typeName);

	if (typeName == TYPENAME_OSCILLATOR)
	{
		ac = new AudioOscillator();
	}
	else if (typeName == TYPENAME_OUTPUT)
	{
		ac = new AudioOutput();
	}
	else if (typeName == TYPENAME_BIQUAD)
	{
		ac = new AudioBiquadFilter();
	}
	else
	{
		Unimplemented();
	}

	return new SynthComponent(scene, name, ac);
}

void SynthComponentFactory::destroySynthComponent(SynthComponent* component)
{
	// TODO who should destroy contained audio object?

	Assert(component);
	delete component;
}
