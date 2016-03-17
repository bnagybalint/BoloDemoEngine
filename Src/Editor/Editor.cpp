#include "Editor.h"

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

void Editor::start(int argc, char** argv)
{
	mQtApplication = new QApplication(argc, argv);
	mMainWindow = new MainWindow();

	//mMainWindow->rendshow();

// 	mQtApplication->exec();
}

void Editor::stop()
{
	delete mMainWindow; mMainWindow = NULL;
	delete mQtApplication; mQtApplication = NULL;
}

HWND Editor::getSceneEditorWindowHandle() const
{
	return mMainWindow->getSceneEditorRenderWidget()->getNativeWindowHandle();
}
