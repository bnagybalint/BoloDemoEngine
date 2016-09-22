#pragma once

#include "Assist/Common.h"

#include "Assist/Array.h"
#include "Assist/Callback.h"
#include "Assist/Delegate.h"
#include "Assist/Mutex.h"
#include "Assist/Signal.h" 
#include "Assist/ObjectUID.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

class EventReactor;
class EditorState;
class EditorInputEvent;

class QApplication;
class MainWindow;
class RenderWidget;

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

	// Change current editor state. Implemented according to the State Machine Pattern.
	// Current editor state is responsible for handling events coming from the render widget(s).
	// Note: ownership of the passed state object is transferred, Editor object is 
	//       responsible for releasing it.
	void changeState(EditorState* nextState);

	// Handle an event coming from (one of the) render widgets. 
	// Input handler part of the State Machine Pattern.
	void processInputEvent(const EditorInputEvent& evt);

	HWND getSceneEditorWindowHandle() const;
	HWND getAudioEditorWindowHandle() const;

	ObjectUID getMainCamera() const { return mMainCameraUid; };
	
private:

	Editor();
	DISABLE_COPY(Editor);
	~Editor();

private:

	void enterEditorMainLoop();

	void processEventCallbacks();

private:

	void onObjectCreated(ObjectUID uid);
	void onObjectDestroying(ObjectUID uid);

private:

	QApplication* mQtApplication;
	MainWindow* mMainWindow;
	RenderWidget* mSceneEditorRenderWidget;
	RenderWidget* mAudioEditorRenderWidget;

	Mutex mEditorLock;
	Array<CallbackBase*> mRequestedCallbacks;

	// Event reactor object that is used to decouple BL events 
	// from the editor and execute them on the editor thread.
	EventReactor* mEventReactor;

	EditorState* mCurrentState;

	ObjectUID mMainCameraUid;
};

