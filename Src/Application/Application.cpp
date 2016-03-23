#include "Application.h"

#include "Assist/Thread.h"
#include "Assist/ThreadManager.h"

#include "Editor/Editor.h"

#include "Render/RenderManager.h"

DEFINE_SINGLETON_IMPL(Application);

Application::Application()
	: mArgc(0)
	, mArgv(NULL)
	, mAppThread(NULL)
	, mEditorThread(NULL)
{
}

Application::~Application()
{
	// TODO release threads
}

int Application::run(int argc, char** argv)
{
	mArgc = argc;
	mArgv = argv;

	// TODO Init stuff that's used by Editor
	ThreadManager::createSingletonInstance();

	// Initialize Editor 
	mEditorThread = ThreadManager::getInstance()->createThread();
	Thread::ThreadTaskDelegate editorStartTask = Thread::ThreadTaskDelegate(this, &Application::startEditorProxy);
	mEditorThread->addTask(editorStartTask);
	mEditorThread->start();
	
	// Initialize App
	mAppThread = ThreadManager::getInstance()->createThread();
	Thread::ThreadTaskDelegate appStartTask = Thread::ThreadTaskDelegate(this, &Application::startAppProxy);
	mAppThread->addTask(appStartTask);
	mAppThread->start();

	// Wait for both App and Editor thread to finish
	Array<Thread*> threadsToJoin;
	threadsToJoin.append(mEditorThread);
	threadsToJoin.append(mAppThread);
	ThreadManager::getInstance()->joinAll(threadsToJoin);

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
