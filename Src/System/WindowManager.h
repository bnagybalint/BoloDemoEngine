#pragma once

#include "Assist/Common.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

class WindowManager
{
public:

	DECLARE_SINGLETON_HEADER(WindowManager);

private:

	static LRESULT CALLBACK WndProcCallback(HWND, UINT, WPARAM, LPARAM);

public:

	void initWindow(unsigned int screenWidth, unsigned int screenHeight);
	void shutdownWindow();

	// Process window messages. Returns false if the normal execution of the 
	// program should be interrupted (quit, destroy, etc.)
	bool processMessages();

	HWND getMainWindowHandle() const { return mMainWindowHandle; }

private:

	WindowManager();
	~WindowManager();

private:

	LPCTSTR      mApplicationName;
	HINSTANCE    mInstanceHandle;
	HWND         mMainWindowHandle;
	unsigned int mWindowWidth;
	unsigned int mWindowHeight;
};

