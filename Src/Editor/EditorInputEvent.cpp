#include "EditorInputEvent.h"

#include <QEvent.h>

namespace
{
	struct EditorInputEventHelper
	{
		static EditorInputEvent::MouseButton translateMouseButton(Qt::MouseButton btn)
		{
			switch (btn)
			{
			case Qt::NoButton:     return EditorInputEvent::MouseButton::None;
			case Qt::LeftButton:   return EditorInputEvent::MouseButton::Left;
			case Qt::MiddleButton: return EditorInputEvent::MouseButton::Middle;
			case Qt::RightButton:  return EditorInputEvent::MouseButton::Right;
			default:               Unimplemented(); break;
			}
			return EditorInputEvent::MouseButton::None;
		}
		static uint32 translateKeyModifiers(Qt::KeyboardModifiers mods)
		{
			uint32 res = 0;
			if (mods & Qt::ShiftModifier) res |= EditorInputEvent::KeyModifier::Shift;
			if (mods & Qt::ControlModifier) res |= EditorInputEvent::KeyModifier::Ctrl;
			if (mods & Qt::AltModifier) res |= EditorInputEvent::KeyModifier::Alt;
			return res;
		}
		static EditorInputEvent::Key translateKey(int key)
		{
			switch (key)
			{
			case Qt::Key::Key_A: return EditorInputEvent::Key::Key_A;
			case Qt::Key::Key_B: return EditorInputEvent::Key::Key_B;
			case Qt::Key::Key_C: return EditorInputEvent::Key::Key_C;
			case Qt::Key::Key_D: return EditorInputEvent::Key::Key_D;
			case Qt::Key::Key_E: return EditorInputEvent::Key::Key_E;
			case Qt::Key::Key_F: return EditorInputEvent::Key::Key_F;
			case Qt::Key::Key_G: return EditorInputEvent::Key::Key_G;
			case Qt::Key::Key_H: return EditorInputEvent::Key::Key_H;
			case Qt::Key::Key_I: return EditorInputEvent::Key::Key_I;
			case Qt::Key::Key_J: return EditorInputEvent::Key::Key_J;
			case Qt::Key::Key_K: return EditorInputEvent::Key::Key_K;
			case Qt::Key::Key_L: return EditorInputEvent::Key::Key_L;
			case Qt::Key::Key_M: return EditorInputEvent::Key::Key_M;
			case Qt::Key::Key_N: return EditorInputEvent::Key::Key_N;
			case Qt::Key::Key_O: return EditorInputEvent::Key::Key_O;
			case Qt::Key::Key_P: return EditorInputEvent::Key::Key_P;
			case Qt::Key::Key_Q: return EditorInputEvent::Key::Key_Q;
			case Qt::Key::Key_R: return EditorInputEvent::Key::Key_R;
			case Qt::Key::Key_S: return EditorInputEvent::Key::Key_S;
			case Qt::Key::Key_T: return EditorInputEvent::Key::Key_T;
			case Qt::Key::Key_U: return EditorInputEvent::Key::Key_U;
			case Qt::Key::Key_V: return EditorInputEvent::Key::Key_V;
			case Qt::Key::Key_W: return EditorInputEvent::Key::Key_W;
			case Qt::Key::Key_X: return EditorInputEvent::Key::Key_X;
			case Qt::Key::Key_Y: return EditorInputEvent::Key::Key_Y;
			case Qt::Key::Key_Z: return EditorInputEvent::Key::Key_Z;

			case Qt::Key::Key_0: return EditorInputEvent::Key::Key_0;
			case Qt::Key::Key_1: return EditorInputEvent::Key::Key_1;
			case Qt::Key::Key_2: return EditorInputEvent::Key::Key_2;
			case Qt::Key::Key_3: return EditorInputEvent::Key::Key_3;
			case Qt::Key::Key_4: return EditorInputEvent::Key::Key_4;
			case Qt::Key::Key_5: return EditorInputEvent::Key::Key_5;
			case Qt::Key::Key_6: return EditorInputEvent::Key::Key_6;
			case Qt::Key::Key_7: return EditorInputEvent::Key::Key_7;
			case Qt::Key::Key_8: return EditorInputEvent::Key::Key_8;
			case Qt::Key::Key_9: return EditorInputEvent::Key::Key_9;

			case Qt::Key::Key_Space:     return EditorInputEvent::Key::Key_Space;
			case Qt::Key::Key_Tab:       return EditorInputEvent::Key::Key_Tab;
			case Qt::Key::Key_Enter:     return EditorInputEvent::Key::Key_Enter;
			case Qt::Key::Key_Escape:    return EditorInputEvent::Key::Key_Escape;
			case Qt::Key::Key_Backspace: return EditorInputEvent::Key::Key_Backspace;
			case Qt::Key::Key_Minus:     return EditorInputEvent::Key::Key_Minus;
			case Qt::Key::Key_Plus:      return EditorInputEvent::Key::Key_Plus;
			case Qt::Key::Key_Insert:    return EditorInputEvent::Key::Key_Insert;
			case Qt::Key::Key_Delete:    return EditorInputEvent::Key::Key_Delete;
			case Qt::Key::Key_Home:      return EditorInputEvent::Key::Key_Home;
			case Qt::Key::Key_End:       return EditorInputEvent::Key::Key_End;
			case Qt::Key::Key_PageUp:    return EditorInputEvent::Key::Key_PgUp;
			case Qt::Key::Key_PageDown:  return EditorInputEvent::Key::Key_PgDown;

			default:                     break;
			}
			return EditorInputEvent::Key::Unmapped; // Unmapped key, ignore
		}
	};
}

/*static*/void EditorInputEvent::translateQtEvent(const QEvent* e, /*ObjectUID widgetUID,*/ /*out*/EditorInputEvent& userEvt)
{
	if (e->type() == QEvent::KeyPress)
	{
		const QKeyEvent* ke = static_cast<const QKeyEvent*>(e);
		//userEvt.widgetUID = widgetUID;
		userEvt.eventType = EventType::KeyDown;
		userEvt.button    = EditorInputEventHelper::translateKey(ke->key());
		userEvt.modifier  = EditorInputEventHelper::translateKeyModifiers(ke->modifiers());
		userEvt.mouseX    = 0;
		userEvt.mouseY    = 0;
	}
	else if (e->type() == QEvent::KeyRelease)
	{
		const QKeyEvent* ke = static_cast<const QKeyEvent*>(e);
		//userEvt.widgetUID = widgetUID;
		userEvt.eventType = EventType::KeyUp;
		userEvt.button    = EditorInputEventHelper::translateKey(ke->key());
		userEvt.modifier  = EditorInputEventHelper::translateKeyModifiers(ke->modifiers());
		userEvt.mouseX    = 0;
		userEvt.mouseY    = 0;
	}
	else if (e->type() == QEvent::MouseMove)
	{
		const QMouseEvent* me = static_cast<const QMouseEvent*>(e);
		//userEvt.widgetUID = widgetUID;
		userEvt.eventType = EventType::MouseMove;
		userEvt.button    = EditorInputEventHelper::translateMouseButton(me->button());
		userEvt.modifier  = EditorInputEventHelper::translateKeyModifiers(me->modifiers());
		userEvt.mouseX    = me->x();
		userEvt.mouseY    = me->y();
	}
	else if (e->type() == QEvent::MouseButtonPress || e->type() == QEvent::MouseButtonDblClick)
	{
		const QMouseEvent* me = static_cast<const QMouseEvent*>(e);
		//userEvt.widgetUID = widgetUID;
		userEvt.eventType = EventType::MouseDown;
		userEvt.button    = EditorInputEventHelper::translateMouseButton(me->button());
		userEvt.modifier  = EditorInputEventHelper::translateKeyModifiers(me->modifiers());
		userEvt.mouseX    = me->x();
		userEvt.mouseY    = me->y();
	}
	else if (e->type() == QEvent::MouseButtonRelease)
	{
		const QMouseEvent* me = static_cast<const QMouseEvent*>(e);
		//userEvt.widgetUID = widgetUID;
		userEvt.eventType = EventType::MouseUp;
		userEvt.button    = EditorInputEventHelper::translateMouseButton(me->button());
		userEvt.modifier  = EditorInputEventHelper::translateKeyModifiers(me->modifiers());
		userEvt.mouseX    = me->x();
		userEvt.mouseY    = me->y();
	}
}
