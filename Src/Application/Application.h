#pragma once

#include "Assist/Common.h"
#include "Assist/Thread.h"

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

private:

	// Program inputs
	int mArgc;
	char** mArgv;

	// Thread for the editor o run on
	Thread mEditorThread;
};

