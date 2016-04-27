#pragma once

#include "Assist/Common.h"

class GraphicsCanvas;
class GraphicsScene;

class Synth
{
public:

	Synth();
	DISABLE_COPY(Synth);
	~Synth();

private:

	GraphicsCanvas* mSynthCanvas;
	GraphicsScene* mSynthScene;
};

