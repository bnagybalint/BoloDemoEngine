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

	void setSceneEditorRenderWidget(QWidget* widget);
	void setAudioEditorRenderWidget(QWidget* widget);

private slots:

	void onTestCreateSynthComponentButtonClicked();

private:

	Ui::MainWindow ui;

	RenderWidget* mSceneEditorRenderWidget;
	RenderWidget* mAudioEditorRenderWidget;
};
