#pragma once

#include "Assist/Common.h"

struct ID2D1Factory;

class Render2DRenderTarget;

class Render2DManager
{
public:

	DECLARE_SINGLETON_HEADER(Render2DManager);

public:

	void init();
	void shutdown();

	ID2D1Factory* getD2DFactory() const { return mFactory; }

private:

	Render2DManager();
	~Render2DManager();

private:

	ID2D1Factory* mFactory;
};

