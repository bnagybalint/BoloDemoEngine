
#include "Editor/Editor.h"
#include "Render/RenderManager.h"

int main(int argc, char** argv)
{
	Editor::createSingletonInstance();

	Editor::getInstance()->start(argc, argv);

	RenderManager::createSingletonInstance();

	HWND hwnd = Editor::getInstance()->getSceneEditorWindowHandle();
	RECT rect;
	GetWindowRect(hwnd, &rect);
	UINT screenWidth = rect.right - rect.left;
	UINT screenHeight = rect.bottom - rect.top;

	RenderManager::getInstance()->initDx(hwnd, screenWidth, screenHeight);

	return 0;
}
