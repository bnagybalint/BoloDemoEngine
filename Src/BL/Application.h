#pragma once

#include "Assist/Common.h"

#include "Assist/Array.h" 
#include "Assist/Mutex.h"
#include "Assist/Signal.h"

class Command;
class Thread;
class Scene;
class SynthScene;

// TODO separate Application into BL/ApplicationStarter and BL/Application classes
class Application
{
	DECLARE_SINGLETON_HEADER(Application);

public:

	Signal basicInitializedSignal;
	Signal totalInitializedSignal;

public:

	int run(int argc, char** argv);

	Scene* getScene() const { return mScene; }
	SynthScene* getSynthScene() const { return mSynth; }

private:

	Application();
	~Application();

private:

	void startEditor();

private:

	void start();

	void initializeBasic();
	void initializeScene();
	void initializeRender();
	void initializeAudio();

	int enterMainLoop();

private:

	// Program inputs
	int mArgc;
	char** mArgv;

	Thread* mAppThread;
	Thread* mEditorThread;

	Scene* mScene;
	SynthScene* mSynth;
};

