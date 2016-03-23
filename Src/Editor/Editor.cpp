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

void Editor::enterEditorMainLoop()
{
	for (;;)
	{
		mQtApplication->processEvents();
		ThreadManager::getInstance()->sleepCurrentThread(5);
	}
}

HWND Editor::getSceneEditorWindowHandle() const
{
	return mMainWindow->getSceneEditorRenderWidget()->getNativeWindowHandle();
}
