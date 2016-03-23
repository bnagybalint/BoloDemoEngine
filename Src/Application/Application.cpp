#include "Application.h"

#include "Editor/Editor.h"

#include "Render/RenderManager.h"

DEFINE_SINGLETON_IMPL(Application);

Application::Application()
	: mArgc(0)
	, mArgv(NULL)
	, mEditorThread()
	, mAppThread()
{
}

Application::~Application()
{
}

int Application::run(int argc, char** argv)
{
	mArgc = argc;
	mArgv = argv;

	// TODO Init stuff that's used by Editor

	// Initialize Editor
	Thread::ThreadTaskDelegate editorStartTask = Thread::ThreadTaskDelegate(this, &Application::startEditorProxy);
	mEditorThread.addTask(editorStartTask);
	mEditorThread.start();
	
	// Initialize App 
	Thread::ThreadTaskDelegate appStartTask = Thread::ThreadTaskDelegate(this, &Application::startAppProxy);
	mAppThread.addTask(appStartTask);
	mAppThread.start();

	// TODO join both threads
	Array<Thread*> threadsToJoin;
	threadsToJoin.append(&mEditorThread);
	threadsToJoin.append(&mAppThread);
	//ThreadManager::getInstance()->joinAll(threadsToJoin);

	return 0;
}

int Application::enterMainLoop()
{
	for (;;)
	{
		// TODO process messages, break loop if necessary
		// TODO process commands
		// TODO step scene
		// TODO render scene
	}
	return 0;
}

void Application::startEditorProxy()
{
	Editor::createSingletonInstance();
	Editor::getInstance()->startEditor(mArgc, mArgv);
	Unimplemented(); // TODO should be initialized on the same thread as exec() is called

	// Start GUI on editor thread
	

}

void Application::startAppProxy()
{
	// Init app
	enterMainLoop();
}

void Application::initializeRender()
{
	//Unimplemented();
}

void Application::initializeAudio()
{
	//Unimplemented();
}
