

#include "Assist/Common.h"
#include "Assist/Color.h"
#include "Assist/Timer.h"
#include "Assist/Vector2.h"
#include "Assist/MathCommon.h"

#include "System/WindowManager.h"

#include "Render/RenderManager.h"

#include "Audio/AudioManager.h"

int main()
{
	// ----- INITIALIZE ENVIRONMENT -----

	WindowManager  ::createSingletonInstance();
	RenderManager  ::createSingletonInstance();
	AudioManager   ::createSingletonInstance();

	WindowManager*   windowMgr   = WindowManager::getInstance();
	RenderManager*   renderMgr   = RenderManager::getInstance();
	AudioManager*    audioMgr    = AudioManager::getInstance();

	const int windowWidth = 800;
	const int windowHeight = 600;
	windowMgr->initWindow(windowWidth, windowHeight);
	renderMgr->initDx(windowMgr->getMainWindowHandle(), windowWidth, windowHeight);
	audioMgr->init(windowMgr->getMainWindowHandle());

	// ----- PLAYGROUND -----

	// ----- ENTER MAIN LOOP -----
#if BDE_GLOBAL_FRAME_LIMITER_FPS > 0
	Timer frameTimer;
#endif
	while (true)
	{
#if BDE_GLOBAL_FRAME_LIMITER_FPS > 0
		frameTimer.start();
#endif

#if BDE_GLOBAL_ENABLE_EDITOR_FUNCTIONALITY
		// ----- PROCESS INPUT -----
		if(!windowMgr->processMessages())
			break;
#endif

		// ----- FRAME START -----

		// TODO scene
		//renderMgr->renderOneFrame();

		// ----- FRAME END -----

#if BDE_GLOBAL_FRAME_LIMITER_FPS > 0
		frameTimer.stop();
		float frameTimeMs = (float)frameTimer.getTimeMilliseconds();
		int sleepTimeMs = int((1000.0f / BDE_GLOBAL_FRAME_LIMITER_FPS) - frameTimeMs);
		if (sleepTimeMs >= 5)
			// sleep no less than 5ms
			Sleep(sleepTimeMs);
#endif
	}

#if BDE_GLOBAL_ENABLE_NICE_DESTROY
	// SHUTDOWN

	audioMgr->shutdown();
	renderMgr->shutdownDx();
	windowMgr->shutdownWindow();

	AudioManager::destroySingletonInstance();
	RenderManager::destroySingletonInstance();
	WindowManager::destroySingletonInstance();
#endif

	return 0;
}
