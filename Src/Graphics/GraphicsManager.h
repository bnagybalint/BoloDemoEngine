#pragma once

#include "Assist/Common.h"
#include "Assist/Map.h"
#include "Assist/String.h"

struct ID2D1Factory;
struct IDWriteFactory;

class GraphicsCanvas;

class GraphicsManager
{
public:

	DECLARE_SINGLETON_HEADER(GraphicsManager);

public:

	void init();
	void shutdown();

	void renderOneFrame();

	GraphicsCanvas* createCanvas(const String& canvasName, HWND windowHandle);
	GraphicsCanvas* getCanvas(const String& canvasName);
	void destroyCanvas(GraphicsCanvas* canvas);

	ID2D1Factory* getD2DFactory() const { return mFactoryD2D; }
	IDWriteFactory* getDWriteFactory() const { return mFactoryDWrite; }

private:

	GraphicsManager();
	~GraphicsManager();

private:

	ID2D1Factory* mFactoryD2D;
	IDWriteFactory* mFactoryDWrite;

	ObjectMap<String, GraphicsCanvas*> mCanvases;
};

