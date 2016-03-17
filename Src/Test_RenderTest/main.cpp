

#include "Assist/Common.h"
#include "Assist/Color.h"
#include "Assist/Timer.h"
#include "Assist/Memory.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <d3d11.h>
#include <stdio.h>

int main()
{
	// enter main loop
	while (true)
	{
#if !COMPILE_DEMO
		// process window messages
		MSG msg; Memory::Memzero(&msg, sizeof(MSG));
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			// process message
			if (msg.message == WM_QUIT)
			{
				goto shutdown;
			}
			else if (msg.message == WM_KEYDOWN)
			{
				char c = MapVirtualKey(msg.wParam, MAPVK_VK_TO_CHAR);
				switch (tolower(c))
				{
				case 0: break;
				default: break;
				}
			}
			else {
				// ignore
			}
		}
#endif

		// FRAME START



		// FRAME END
	}

#if !COMPILE_DEMO
shutdown:
	// SHUTDOWN

#endif

	return 0;
}