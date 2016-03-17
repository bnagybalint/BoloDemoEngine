#pragma once

#include "Assist\Common.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

class MainWindow;

class QApplication;

class Editor
{
public:

	DECLARE_SINGLETON_HEADER(Editor);

public:

	void start(int argc, char** argv);
	void stop();

	HWND getSceneEditorWindowHandle() const;

private:

	Editor();
	~Editor();

private:

	QApplication* mQtApplication;
	MainWindow* mMainWindow;

};

