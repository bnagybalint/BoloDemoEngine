#include "Application.h"

#include "Assist/Thread.h"
#include "Assist/ThreadManager.h"
#include "Assist/UIDGenerator.h"

#include "Editor/Editor.h"

#include "Model/Command.h"

#include "Render/RenderManager.h"

DEFINE_SINGLETON_IMPL(Application);

Application::Application()
	: mArgc(0)
	, mArgv(NULL)
	, mAppThread(NULL)
	, mEditorThread(NULL)
	, mApplicationLock()
	, mCommands()
	, mTestCounter(0)
{
}

Application::~Application()
{
	// TODO release threads

	mApplicationLock.lock();
	for (int i = 0; i < mCommands.size(); i++)
	{
		delete mCommands[i]; mCommands[i] = NULL;
	}
	mApplicationLock.release();
}

int Application::run(int argc, char** argv)
{
	mArgc = argc;
	mArgv = argv;

	UIDGenerator::createSingletonInstance();
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
		
		processCommands();

		// TODO step scene
		// TODO render scene

		// TODO remove test stuff :D
		mTestCounter++;
		testCounterChanged.fire(mTestCounter);
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
	Unimplemented();
}

void Application::initializeAudio()
{
	Unimplemented();
}

void Application::addCommand(Command* cmd)
{
	mApplicationLock.lock();
	mCommands.append(cmd);
	mApplicationLock.release();
}

void Application::processCommands()
{
	mApplicationLock.lock();
	for (int i = 0; i < mCommands.size(); i++)
	{
		Command* cmd = mCommands[i];

		cmd->execute();

		Command::ResultCode sc = cmd->getResultCode();

		delete mCommands[i]; mCommands[i] = NULL;
	}
	mApplicationLock.release();
}