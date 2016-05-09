#pragma once

#include "Assist/Common.h"

#include "Assist/String.h"

class SynthComponent;
class SynthScene;

class SynthComponentFactory
{
public:

	DECLARE_SINGLETON_HEADER(SynthComponentFactory);

public:

	static const char* TYPENAME_OSCILLATOR;
	static const char* TYPENAME_BIQUAD;
	static const char* TYPENAME_OUTPUT;

public:

	SynthComponent* createSynthComponent(const String& typeName, SynthScene* scene);
	void destroySynthComponent(SynthComponent* component);

private:

	SynthComponentFactory();
	~SynthComponentFactory();
};

