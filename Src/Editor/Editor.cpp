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

void Editor::initialize(int argc, char** argv)
{
	mQtApplication = new QApplication(argc, argv);
	mMainWindow = new MainWindow();

	mMainWindow->show();
}

void Editor::startGui()
{
	int exitCodeGui = mQtApplication->exec();

	Assert(exitCodeGui == 0);

	// TODO request application terminate
}

void Editor::stopGui()
{
	Unimplemented();
	delete mMainWindow; mMainWindow = NULL;
	delete mQtApplication; mQtApplication = NULL;
}

HWND Editor::getSceneEditorWindowHandle() const
{
	return mMainWindow->getSceneEditorRenderWidget()->getNativeWindowHandle();
}
