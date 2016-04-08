#pragma once

#include "Assist/Common.h"

#include "Assist/Array.h"
#include "Assist/Callback.h"
#include "Assist/Delegate.h"
#include "Assist/Mutex.h"
#include "Assist/Signal.h"

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

	Signal initializedSignal;

public:

	void startEditor(int argc, char** argv);
	void stopEditor();

	// Used to register a callback, which is called from the Editor thread, the next time when the Editor is processing events.
	// Note: ownership of the callback object is transferred, Editor object will release the callback object.
	void requestEventCallback(CallbackBase* cb);

	HWND getSceneEditorWindowHandle() const;

private:

	Editor();
	~Editor();

private:

	void enterEditorMainLoop();

private:

	QApplication* mQtApplication;
	MainWindow* mMainWindow;

	Mutex mEditorLock;
	Array<CallbackBase*> mRequestedCallbacks;
};

