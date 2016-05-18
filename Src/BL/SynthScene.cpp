#include "SynthScene.h"

#include "Graphics/GraphicsManager.h"
#include "Graphics/GraphicsScene.h"
#include "Graphics/GraphicsCanvas.h"

// ONLY FOR TEST INITIALIZATION, REMOVE LATER
#include "Graphics/GraphicsNode.h"
#include "Graphics/GraphicsRectangle.h"
#include "Graphics/GraphicsText.h"
#include "BL/SynthComponent.h"
#include "Audio/AudioOscillator.h"

SynthScene::SynthScene(HWND parentWindow)
	: mSynthCanvas(NULL)
	, mSynthScene(NULL)
	, mObjects()
	, mPicker(NULL)
{
	mSynthCanvas = GraphicsManager::getInstance()->createCanvas("AudioEditorCanvas", parentWindow);

	mSynthScene = new GraphicsScene();
	mSynthCanvas->setScene(mSynthScene);

	mPicker = new Picker2D();
}

SynthScene::~SynthScene()
{
	delete mPicker; mPicker = NULL;
	
	mSynthCanvas->setScene(NULL);
	delete mSynthScene; mSynthScene = NULL;

	GraphicsManager::getInstance()->destroyCanvas(mSynthCanvas); mSynthCanvas = NULL;
}

void SynthScene::addObject(SynthObject* obj)
{
	Assert(!mObjects.contains(obj->getName()));
	mObjects.add(obj->getName(), obj);
}

void SynthScene::removeObject(SynthObject* obj)
{
	Assert(mObjects.contains(obj->getName()));
	mObjects.remove(obj->getName());
}
