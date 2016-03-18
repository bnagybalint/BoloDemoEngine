#include "RenderWidget.h"

RenderWidget::RenderWidget(QWidget* parent)
	: QWidget(parent)
{
}

RenderWidget::~RenderWidget()
{
}

HWND RenderWidget::getNativeWindowHandle() const
{
	WId wid = effectiveWinId();
	return (HWND)wid;
}
