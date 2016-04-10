#include "MainWindow.h"

#include "RenderWidget.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

MainWindow::~MainWindow()
{
	
}

void MainWindow::setSceneEditorRenderWidget(QWidget* widget)
{
	ui.sceneEditorTab->layout()->addWidget(widget);
}

void MainWindow::setAudioEditorRenderWidget(QWidget* widget)
{
	ui.audioEditorTab->layout()->addWidget(widget);
}
