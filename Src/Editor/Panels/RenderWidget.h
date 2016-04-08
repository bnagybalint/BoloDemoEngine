#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

#include "Assist/Common.h"

#include <QWidget>

#include "Assist/Delegate.h"
#include "Assist/Event.h"

class QPaintEngine;

class RenderWidget : public QWidget
{
	Q_OBJECT

public:

	Event<int, int> renderAreaChangedEvent;

public:

	RenderWidget(QWidget* parent = NULL);
	~RenderWidget();

	HWND getNativeWindowHandle() const;

	QPaintEngine* paintEngine() const override { return NULL; }
};

