#include "RenderWidget.h"

#include "Editor/EditorInputEvent.h"
#include "Editor/Editor.h"

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

	bool shouldHandle = false;
	if (e->type() == QEvent::MouseMove)
	{
		QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(e);
		//DebugConsole("On widget 0x%016lx: Mouse MOVE: (%u,%u)\n", (uint64)this, mouseEvent->pos().x(), mouseEvent->pos().y());
		shouldHandle = true;
	}
	else if (e->type() == QEvent::MouseButtonPress
		|| e->type() == QEvent::MouseButtonDblClick)
	{
		if (!hasFocus())
		{
			setFocus();
			DebugConsole("FOCUS obtained!\n");
		}

		if (hasFocus())
			DebugConsole("HAS FOCUS :: ");
		DebugConsole("On widget 0x%016lx: Mouse button DOWN\n", (uint64)this);
		shouldHandle = true;

	}
	else if (e->type() == QEvent::MouseButtonRelease)
	{
		if (hasFocus())
			DebugConsole("HAS FOCUS :: ");
		DebugConsole("On widget 0x%016lx: Mouse button UP\n", (uint64)this);
		shouldHandle = true;
	}
	else if (e->type() == QEvent::KeyPress)
	{
		if (hasFocus())
			DebugConsole("HAS FOCUS :: ");
		QKeyEvent* keyEvent = static_cast<QKeyEvent*>(e);
		DebugConsole("On widget 0x%016lx: Key DOWN: %d ('%c')\n", (uint64)this, keyEvent->key(), (char)keyEvent->key());
		shouldHandle = true;
	}
	else if (e->type() == QEvent::KeyRelease)
	{
		if (hasFocus())
			DebugConsole("HAS FOCUS :: ");
		QKeyEvent* keyEvent = static_cast<QKeyEvent*>(e);
		DebugConsole("On widget 0x%016lx: Key UP: %d ('%c')\n", (uint64)this, keyEvent->key(), (char)keyEvent->key());
		shouldHandle = true;
	}
	else
	{
		// NOP
	}

	if (shouldHandle)
	{
		EditorInputEvent eEvt;
		EditorInputEvent::translateQtEvent(e, eEvt);
		Editor::getInstance()->processInputEvent(eEvt);
	}

	return false;
}
