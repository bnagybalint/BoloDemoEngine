#include "MainWindow.h"

#include "RenderWidget.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, mSceneEditorWidget(NULL)
{
	ui.setupUi(this);

	mSceneEditorWidget = new RenderWidget(ui.sceneEditorTab);
}

MainWindow::~MainWindow()
{
	delete mSceneEditorWidget; mSceneEditorWidget = NULL;
}
