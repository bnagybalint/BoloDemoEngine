#include "Editor.h"

#include "Assist/ThreadManager.h"
#include "Assist/Logger.h"

#include "Editor/EventReactor.h"

#include "Editor/Panels/MainWindow.h"
#include "Editor/Panels/RenderWidget.h" 

#include <QApplication>

// Define singleton parts
DEFINE_SINGLETON_IMPL(Editor);

Editor::Editor()
	: mQtApplication(NULL)
	, mMainWindow(NULL)
	, mSceneEditorRenderWidget(NULL)
	, mAudioEditorRenderWidget(NULL)

	, mEditorLock()
	, mRequestedCallbacks()
	, mEventReactor(NULL)
{
	mEventReactor = new EventReactor();
}

Editor::~Editor()
{
	delete mEventReactor; mEventReactor = NULL;
}

void Editor::startEditor(int argc, char** argv)
{
	LOGINFO("Starting Editor");

	LOGINFO("Creating Qt window");
	mQtApplication = new QApplication(argc, argv);
	mMainWindow = new MainWindow();

	mSceneEditorRenderWidget = new RenderWidget();
	mMainWindow->setSceneEditorRenderWidget(mSceneEditorRenderWidget);
	
	mAudioEditorRenderWidget = new RenderWidget();
	mMainWindow->setAudioEditorRenderWidget(mAudioEditorRenderWidget);

	mMainWindow->show();

	LOGINFO("---> Editor initialized");

	initializedSignal.send();

	LOGINFO("Entering editor main loop");

	enterEditorMainLoop();
}

void Editor::stopEditor()
{
	Unimplemented();
	delete mMainWindow; mMainWindow = NULL;
	delete mQtApplication; mQtApplication = NULL;
}

void Editor::requestEventCallback(CallbackBase* cb)
{
	mEditorLock.lock();
	mEventReactor->registerEvent(cb);
	mEditorLock.release();
}

void Editor::processEventCallbacks()
{
	mEditorLock.lock();
	mEventReactor->processEvents();
	mEditorLock.release();
}

void Editor::enterEditorMainLoop()
{
	for (;;)
	{
		// TODO check exit condition

		// Invoke callbacks registered since last time.
		processEventCallbacks();

		// Let Qt process window events.
		mQtApplication->processEvents();

		// Sleep thread for a while...
		ThreadManager::getInstance()->sleepCurrentThread(5);
	}
}


HWND Editor::getSceneEditorWindowHandle() const
{
	return mSceneEditorRenderWidget->getNativeWindowHandle();
}

HWND Editor::getAudioEditorWindowHandle() const
{
	return mAudioEditorRenderWidget->getNativeWindowHandle();
}
