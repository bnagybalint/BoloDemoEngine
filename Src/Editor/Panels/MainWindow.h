#pragma once

#include "Assist/Common.h"
#include "Assist/Array.h"

#include "ui_MainWindow.h"

#include <QMainWindow>

class RenderWidget;

class QWidget;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:

	MainWindow(QWidget* parent = NULL);
	~MainWindow();

	RenderWidget* getSceneEditorRenderWidget() const { return mSceneEditorWidget; }

private:

	Ui::MainWindow ui;

	RenderWidget* mSceneEditorWidget;
};
