#pragma once

#include "Assist/Common.h"

class Thread;

class Application
{
	DECLARE_SINGLETON_HEADER(Application);

public:

	int run(int argc, char** argv);

private:

	Application();
	~Application();

private:

	void initializeRender();
	void initializeAudio();

	int enterMainLoop();

	void startEditorProxy();
	void startAppProxy();

private:

	// Program inputs
	int mArgc;
	char** mArgv;

	Thread* mAppThread;
	Thread* mEditorThread;
};

