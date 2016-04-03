#include "Editor.h"

#include "Assist/ThreadManager.h"

#include "Panels/MainWindow.h"
#include "Panels/RenderWidget.h" 

#include <QApplication>

// Define singleton parts
DEFINE_SINGLETON_IMPL(Editor);

Editor::Editor()
	: mQtApplication(NULL)
	, mMainWindow(NULL)
	, mEditorLock()
	, mRequestedCallbacks()
{
}

Editor::~Editor()
{
}

void Editor::startEditor(int argc, char** argv)
{
	mQtApplication = new QApplication(argc, argv);
	mMainWindow = new MainWindow();

	mMainWindow->show();

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
	mRequestedCallbacks.append(cb);
	mEditorLock.release();
}

void Editor::enterEditorMainLoop()
{
	for (;;)
	{
		// TODO check exit condition

		// Invoke callbacks registered since last time.
		mEditorLock.lock();
		for (int i = 0; i < mRequestedCallbacks.size(); i++)
		{
			mRequestedCallbacks[i]->call();
			delete mRequestedCallbacks[i]; mRequestedCallbacks[i] = NULL;
		}
		mEditorLock.release();

		// Let Qt process window events.
		mQtApplication->processEvents();

		// Sleep thread for a while...
		ThreadManager::getInstance()->sleepCurrentThread(5);
	}
}

HWND Editor::getSceneEditorWindowHandle() const
{
	return mMainWindow->getSceneEditorRenderWidget()->getNativeWindowHandle();
}
