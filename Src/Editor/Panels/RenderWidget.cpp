#include "RenderWidget.h"

RenderWidget::RenderWidget(QWidget* parent)
	: QWidget(parent)
{
	setAttribute(Qt::WA_PaintOnScreen, true);
	setAttribute(Qt::WA_NativeWindow, true);
}

RenderWidget::~RenderWidget()
{
}

void RenderWidget::resizeEvent(QResizeEvent*)
{
	// TODO do something upon (re)sizing
	//Unimplemented();
}
void RenderWidget::paintEvent(QPaintEvent*)
{
	// NOP, rendering is handled by the Application.
}

HWND RenderWidget::getNativeWindowHandle() const
{
	// This is not the official way, but it works.
	WId wid = effectiveWinId();
	return (HWND)wid;
}
