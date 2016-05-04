#include "SynthScene.h"

#include "Editor/Editor.h"

#include "Graphics/GraphicsManager.h"
#include "Graphics/GraphicsScene.h"
#include "Graphics/GraphicsCanvas.h"

// ONLY FOR TEST INITIALIZATION, REMOVE LATER
#include "Graphics/GraphicsNode.h"
#include "Graphics/GraphicsRectangle.h"
#include "Graphics/GraphicsText.h"

DEFINE_SINGLETON_IMPL(SynthScene);

SynthScene::SynthScene()
	: mSynthCanvas(NULL)
	, mSynthScene(NULL)
{
	mSynthCanvas = GraphicsManager::getInstance()->createCanvas("AudioEditorCanvas", Editor::getInstance()->getAudioEditorWindowHandle());

	mSynthScene = new GraphicsScene();
	mSynthCanvas->setScene(mSynthScene);

// 	// TEST INITIALIZATION, REMOVE LATER
// 	static GraphicsNode* testNode = new GraphicsNode();
// 	static GraphicsRectangle* testObj = new GraphicsRectangle();
// 	static GraphicsText* testObj2 = new GraphicsText();
// 
// 	testObj->setSize(Vector2(150,60));
// 	
// 	testObj->setFillColor(Color(0.8, 0.8, 0.8));
// 	testObj->setBorderColor(Color(0.2, 0.2, 0.2));
// 	testObj->setBorderWidth(1.5f);
// 
// 	testObj2->setText("Test");
// 	testObj2->setFontSize(24.0f);
// 	testObj2->setFontFamily("Courier New");
// 	testObj2->setTextAlignment(GraphicsText::TextAlignment::MidCenter);
// 	
// 
// 	testNode->setPosition(Vector2(0, 0));
// 
// 	testNode->addObject(testObj);
// 	testNode->addObject(testObj2);
// 	mSynthScene->addNode(testNode, NULL);
}

SynthScene::~SynthScene()
{
	mSynthCanvas->setScene(NULL);
	delete mSynthScene; mSynthScene = NULL;

	GraphicsManager::getInstance()->destroyCanvas(mSynthCanvas); mSynthCanvas = NULL;
}
