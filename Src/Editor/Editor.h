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

	void startEditor(int argc, char** argv);
	void stopEditor();

	HWND getSceneEditorWindowHandle() const;

private:

	Editor();
	~Editor();

private:

	void enterEditorMainLoop();

private:

	QApplication* mQtApplication;
	MainWindow* mMainWindow;

};

