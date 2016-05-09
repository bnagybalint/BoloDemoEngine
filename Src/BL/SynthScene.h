#pragma once

#include "Assist/Common.h"

#include "Assist/Map.h"
#include "Assist/String.h"

class GraphicsCanvas;
class GraphicsScene;

class SynthObject;
class SynthComponent;

class SynthScene
{
public:

	SynthScene(HWND parentWindow);
	DISABLE_COPY(SynthScene);
	~SynthScene();

	void addObject(SynthObject* obj);
	void removeObject(SynthObject* obj);

	GraphicsScene* getRenderScene() const { return mSynthScene; }

private:

	GraphicsCanvas* mSynthCanvas;
	GraphicsScene* mSynthScene;

	Map<String, SynthObject*> mObjects; // object.name -> object
};

