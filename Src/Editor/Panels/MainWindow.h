#pragma once

#include "Assist/Common.h"
#include "Assist/Array.h"

#include "ui_MainWindow.h"

#include <QMainWindow>

// TODO debug
#include "Assist/String.h"

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

	// TODO debug
	void debug_onPropertyChange(ObjectUID propOwnerUID, const String& propName);

private:

	Ui::MainWindow ui;

	RenderWidget* mSceneEditorWidget;
};
