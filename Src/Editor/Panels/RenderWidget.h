#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

#include "Assist/Common.h"

#include <QWidget>

class RenderWidget : public QWidget
{
	Q_OBJECT

public:

	RenderWidget(QWidget* parent = NULL);
	~RenderWidget();

	HWND getNativeWindowHandle() const;
};

