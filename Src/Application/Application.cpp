#include "Application.h"

#include "Editor/Editor.h"

#include "Render/RenderManager.h"

DEFINE_SINGLETON_IMPL(Application);

Application::Application()
	: mArgc(0)
	, mArgv(NULL)
	, mEditorThread()
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
	Editor::createSingletonInstance();
	Editor::getInstance()->initialize(mArgc, mArgv);
	Unimplemented(); // TODO should be initialized on the same thread as exec() is called

	// Start GUI on editor thread
	Thread::ThreadTaskDelegate editorStartTask = Thread::ThreadTaskDelegate(Editor::getInstance(), &Editor::startGui);
	mEditorThread.addTask(editorStartTask);
	mEditorThread.start();

	// Initialize Direct3D
	initializeRender();

	// Initialize DirectSound
	initializeAudio();

	// TODO Init stuff that needs Editor (e.g. DirectX, DirectAudio)

	return enterMainLoop();
}

void Application::initializeRender()
{
	//Unimplemented();
}

void Application::initializeAudio()
{
	//Unimplemented();
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
