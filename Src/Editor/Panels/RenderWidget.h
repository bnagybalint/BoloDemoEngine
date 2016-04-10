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

	RenderWidget(QWidget* parent = NULL);
	~RenderWidget();

	HWND getNativeWindowHandle() const;

	QPaintEngine* paintEngine() const override { return NULL; }

protected:

	virtual void resizeEvent(QResizeEvent* evt);
	virtual void paintEvent(QPaintEvent* evt);
};

