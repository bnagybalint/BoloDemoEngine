#include "Application.h"

#include "Assist/Logger.h"
#include "Assist/Thread.h"
#include "Assist/ThreadManager.h"
#include "Assist/UIDGenerator.h"

#include "Editor/Editor.h"

#include "Audio/AudioManager.h"

#include "Render/RenderManager.h"

#include "Graphics/GraphicsManager.h"

#include "BL/Scene.h"
#include "BL/Synth.h"
#include "BL/Command.h"

DEFINE_SINGLETON_IMPL(Application);

Application::Application()
	: mArgc(0)
	, mArgv(NULL)
	, mAppThread(NULL)
	, mEditorThread(NULL)
	, mApplicationLock()
	, mCommands()
	, mScene(NULL)
	, mSynth(NULL)
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

	initializeBasic();
	LOGINFO("---> Application basic functionality reached.");

	// Initialize App
	LOGINFO("Starting Application thread...");
	mAppThread = ThreadManager::getInstance()->createThread();
	Thread::ThreadTaskDelegate appStartTask = Thread::ThreadTaskDelegate(this, &Application::start);
	mAppThread->addTask(appStartTask);
	mAppThread->start();

	// Initialize Editor
	LOGINFO("Starting Editor thread...");
	mEditorThread = ThreadManager::getInstance()->createThread();
	Thread::ThreadTaskDelegate editorStartTask = Thread::ThreadTaskDelegate(this, &Application::startEditor);
	mEditorThread->addTask(editorStartTask);
	mEditorThread->start();
	
	// Wait for both App and Editor thread to finish
	Array<Thread*> threadsToJoin;
	threadsToJoin.append(mEditorThread);
	threadsToJoin.append(mAppThread);
	ThreadManager::getInstance()->joinAll(threadsToJoin);

	LOGINFO("Exiting...");
	return 0;
}

void Application::startEditor()
{
	Editor::getInstance()->startEditor(mArgc, mArgv);
}

void Application::start()
{
	LOGINFO("Waiting for editor to initialize...");
	Editor::getInstance()->initializedSignal.wait();

	initializeRender();
	initializeAudio();
	initializeScene();

	LOGINFO("---> Application total functionality reached");

	LOGINFO("Entering main loop");
	enterMainLoop();
}

void Application::initializeBasic()
{
	Logger::createSingletonInstance();
	LOGINFO("Logger created.");
	
	LOGINFO("--- BoloDemoEditor ---");
	LOGINFO("                      ");
	LOGINFO("      (rawr!)         ");
	LOGINFO("                      ");
	LOGINFO("----------------------");

	UIDGenerator::createSingletonInstance();
	ThreadManager::createSingletonInstance();

	Editor::createSingletonInstance();
}

void Application::initializeScene()
{
	LOGINFO("Initializing scene");
	
	mScene = new Scene();
	mSynth = new Synth();
}

void Application::initializeRender()
{
	LOGINFO("Initializing graphics subsystem");

	Editor* editor = Editor::getInstance();

	// 3D Render

	RenderManager::createSingletonInstance();
	RenderManager* renderMgr = RenderManager::getInstance();
	renderMgr->initDx(editor->getSceneEditorWindowHandle());

	// 2D Render

	GraphicsManager::createSingletonInstance();
	GraphicsManager* graphicsMgr = GraphicsManager::getInstance();
	graphicsMgr->init();
}

void Application::initializeAudio()
{
	LOGINFO("Initializing Audio subsystem");
// 	AudioManager::createSingletonInstance();
// 	AudioManager* audioMgr = AudioManager::getInstance();
// 	audioMgr->init();
}

int Application::enterMainLoop()
{
	for (;;)
	{
		// TODO process messages, break loop if necessary
		
		processCommands();

		// Render 3D view
		RenderManager::getInstance()->renderOneFrame();

		// Render 2D views
		GraphicsManager::getInstance()->renderOneFrame();

		// Sleep thread for a while...
		ThreadManager::getInstance()->sleepCurrentThread(5);
	}
	return 0;
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