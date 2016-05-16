#include "RenderWidget.h"

#include <QEvent.h>
#include <QObject.h>

RenderWidget::RenderWidget(QWidget* parent)
	: QWidget(parent)
{
	setAttribute(Qt::WA_PaintOnScreen, true);
	setAttribute(Qt::WA_NativeWindow, true);

	installEventFilter(this);
	setMouseTracking(true);
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

bool RenderWidget::eventFilter(QObject* obj, QEvent* e)
{
	Assert(obj == this);

	if (e->type() == QEvent::MouseMove)
	{
		QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(e);
		DebugConsole("On widget 0x%016lx: Mouse moved (%u,%u)\n", (uint64)this, mouseEvent->pos().x(), mouseEvent->pos().y());
	}
	else
	{
		// NOP
	}
	return false;
}
