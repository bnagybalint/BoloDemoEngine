#pragma once

#include "Assist/Array.h"
#include "Assist/Common.h" 
#include "Assist/Event.h"
#include "Assist/Mutex.h"

class Command;
class Thread;

class Application
{
	DECLARE_SINGLETON_HEADER(Application);

public:

	Event<int> testCounterChanged;

public:

	int run(int argc, char** argv);

	// Commands are deferred execution units, that are used to defer work to a later point in time
	// NOTE: this is reserved for Editor-Application communication, Application objects should not create and issue Commands.
	// NOTE: ownership of the command object is transferred, Application object will release the command object.
	void addCommand(Command* cmd);

private:

	Application();
	~Application();

private:

	void initialize();
	void initializeRender();
	void initializeAudio();

	int enterMainLoop();

	void startEditorProxy();
	void startAppProxy();

	// Process commands accumulated since last time this function was called
	void processCommands();

private:

	// Program inputs
	int mArgc;
	char** mArgv;

	Thread* mAppThread;
	Thread* mEditorThread;

	Mutex mApplicationLock;
	Array<Command*> mCommands;

	int mTestCounter;
};

