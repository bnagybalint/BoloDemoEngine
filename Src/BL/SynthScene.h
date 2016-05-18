#pragma once

#include "Assist/Common.h"

#include "Assist/Map.h"
#include "Assist/String.h"

class GraphicsCanvas;
class GraphicsScene;

class SynthObject;
class SynthComponent;
class Picker2D;

class SynthScene
{
public:

	SynthScene(HWND parentWindow);
	DISABLE_COPY(SynthScene);
	~SynthScene();

	void addObject(SynthObject* obj);
	void removeObject(SynthObject* obj);

	GraphicsScene* getRenderScene() const { return mSynthScene; }

	Picker2D* getPicker() const { return mPicker; }

private:

	GraphicsCanvas* mSynthCanvas;
	GraphicsScene* mSynthScene;

	Map<String, SynthObject*> mObjects; // object.name -> object

	Picker2D* mPicker;
};

