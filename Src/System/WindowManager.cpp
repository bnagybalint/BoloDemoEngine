#include "WindowManager.h"

#include "Assist/Memory.h"

// Define singleton parts
DEFINE_SINGLETON_IMPL(WindowManager);

WindowManager::WindowManager()
{
}

WindowManager::~WindowManager()
{
	// TODO ?
}

void WindowManager::initWindow(unsigned int screenWidth, unsigned int screenHeight)
{
	mApplicationName = "TEST";
	mWindowWidth = screenWidth;
	mWindowHeight = screenHeight;

	WNDCLASSEX wc;
	int posX, posY;

	// Get the instance of this application.
	mInstanceHandle = GetModuleHandle(NULL);

	// Setup the windows class with default settings.
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WindowManager::WndProcCallback;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = mInstanceHandle;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = mApplicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	// Register the window class.
	RegisterClassEx(&wc);

	posX = (GetSystemMetrics(SM_CXSCREEN) - mWindowWidth) / 2;
	posY = (GetSystemMetrics(SM_CYSCREEN) - mWindowHeight) / 2;

	// Create the window with the screen settings and get the handle to it.
	mMainWindowHandle = CreateWindowEx(WS_EX_APPWINDOW, mApplicationName, mApplicationName, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		posX, posY, mWindowWidth, mWindowHeight, NULL, NULL, mInstanceHandle, NULL);

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(mMainWindowHandle, SW_SHOW);
	SetForegroundWindow(mMainWindowHandle);
	SetFocus(mMainWindowHandle);

	// Hide the mouse cursor.
	ShowCursor(false);

	return;
}

void WindowManager::shutdownWindow()
{
	// Show the mouse cursor.
	ShowCursor(true);

	// Remove the window.
	Assert(mMainWindowHandle);
	DestroyWindow(mMainWindowHandle); mMainWindowHandle = NULL;

	// Remove the application instance.
	UnregisterClass(mApplicationName, mInstanceHandle); mInstanceHandle = NULL;
}

LRESULT CALLBACK WindowManager::WndProcCallback(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	//FIXME is function this even needed/necessary for a demo?

	switch (umessage)
	{
	// Check if the window is being destroyed.
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}

	// Check if the window is being closed.
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}

	// All other messages pass to the message handler in the system class.
	default:
	{
		// ignore
		return DefWindowProc(hwnd, umessage, wparam, lparam);
	}
	}
}

bool WindowManager::processMessages()
{
	// process window messages
	MSG msg; Memory::Memzero(&msg, sizeof(MSG));
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		// process message
		if (msg.message == WM_QUIT)
		{
			return false;
		}
		else if (msg.message == WM_KEYDOWN)
		{
			char c = (char)MapVirtualKey(msg.wParam, MAPVK_VK_TO_CHAR);
			switch (tolower(c))
			{
			case 27: // ESC
				return true;
			default:
				break;
			}
		}
		else {
			// ignore
		}
	}

	return true;
}
