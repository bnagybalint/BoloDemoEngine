#pragma once

#include "Assist/Common.h"

class GraphicsCanvas;
class GraphicsScene;

class SynthScene
{
public:

	DECLARE_SINGLETON_HEADER(SynthScene);

public:

	GraphicsScene* getRenderScene() const { return mSynthScene; }

private:

	SynthScene();
	DISABLE_COPY(SynthScene);
	~SynthScene();

private:

	GraphicsCanvas* mSynthCanvas;
	GraphicsScene* mSynthScene;
};

