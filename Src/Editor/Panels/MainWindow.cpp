#include "MainWindow.h"

#include "Editor/Panels/RenderWidget.h"

#include "BL/CommandManager.h"
#include "BL/CreateSynthComponentCommand.h"

#include "Assist/Vector2.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui()
	, mSceneEditorRenderWidget(NULL)
	, mAudioEditorRenderWidget(NULL)
{
	ui.setupUi(this);

	connect(ui.timelineWidget_playPausePushButton, SIGNAL(clicked()), this, SLOT(onTestCreateSynthComponentButtonClicked()));
}

MainWindow::~MainWindow()
{
	
}

void MainWindow::setSceneEditorRenderWidget(QWidget* widget)
{
	Assert(!mSceneEditorRenderWidget);

	mSceneEditorRenderWidget = dynamic_cast<RenderWidget*>(widget);
	Assert(mSceneEditorRenderWidget);

	ui.sceneEditorTab->layout()->addWidget(widget);
}

void MainWindow::setAudioEditorRenderWidget(QWidget* widget)
{
	Assert(!mAudioEditorRenderWidget);

	mAudioEditorRenderWidget = dynamic_cast<RenderWidget*>(widget);
	Assert(mAudioEditorRenderWidget);

	ui.audioEditorTab->layout()->addWidget(widget);
}

void MainWindow::onTestCreateSynthComponentButtonClicked()
{
	Command* cmd = new CreateSynthComponentCommand("oscillator", Vector2::ZERO);
	CommandManager::getInstance()->addCommand(cmd);
}

