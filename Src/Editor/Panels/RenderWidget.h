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

private:
	typedef Event<int, int> RenderAreaChangedEvent;

public:
	typedef RenderAreaChangedEvent::EventHandlerDelegate RenderAreaChangedDelegate;
	RenderAreaChangedEvent renderAreaChanged;

public:

	RenderWidget(QWidget* parent = NULL);
	~RenderWidget();

	HWND getNativeWindowHandle() const;

	QPaintEngine* paintEngine() const override { return NULL; }
};

