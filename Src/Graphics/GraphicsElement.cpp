#include "GraphicsElement.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>


GraphicsElement::GraphicsElement()
	: mLocalPosition(Vector2(0.0f, 0.0f))
	, mLocalOrientation(0.0f)
	, mZOrder(0)
{
}

GraphicsElement::~GraphicsElement()
{
}
