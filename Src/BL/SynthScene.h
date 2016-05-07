#pragma once

#include "Assist/Common.h"

class GraphicsCanvas;
class GraphicsScene;

class SynthScene
{
public:

	SynthScene(HWND parentWindow);
	DISABLE_COPY(SynthScene);
	~SynthScene();

public:

	GraphicsScene* getRenderScene() const { return mSynthScene; }

private:

	GraphicsCanvas* mSynthCanvas;
	GraphicsScene* mSynthScene;
};

