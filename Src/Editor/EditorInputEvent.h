#pragma once

#include "Assist/Common.h"

class QEvent;

class EditorInputEvent
{
public:

	EnumBegin(EventType, MouseMove)
		MouseMove = 0,
		MouseDown = 1,
		MouseUp   = 2,
		KeyDown   = 3,
		KeyUp     = 4,
	EnumEnd(EventType)

	EnumBegin(MouseButton, None)
		None   = 0,
		Left   = 1,
		Middle = 2,
		Right  = 3,
	EnumEnd(MouseButton)
			
	EnumBegin(KeyModifier, None)
		None  = 1 << 0,
		Ctrl  = 1 << 1,
		Shift = 1 << 2,
		Alt   = 1 << 3,
	EnumEnd(KeyModifier)

	EnumBegin(Key, None)
		None = 0,
		Unmapped = 1,

		Key_ALPHABET_START,
		Key_A, Key_B, Key_C, Key_D, Key_E,
		Key_F, Key_G, Key_H, Key_I, Key_J,
		Key_K, Key_L, Key_M, Key_N, Key_O,
		Key_P, Key_Q, Key_R, Key_S, Key_T,
		Key_U, Key_V, Key_W, Key_X, Key_Y,
		Key_Z,
		Key_ALPHABET_END,
	
		Key_NUMBERS_START,
		Key_0, Key_1, Key_2, Key_3, Key_4,
		Key_5, Key_6, Key_7, Key_8, Key_9,
		Key_NUMBERS_END,

		Key_SPECIAL_START,
		Key_Space,
		Key_Tab,
		Key_Enter,
		Key_Escape,
		Key_Backspace,
		Key_Minus,
		Key_Plus,
		Key_Insert,
		Key_Delete,
		Key_Home,
		Key_End,
		Key_PgUp,
		Key_PgDown,
		Key_SPECIAL_END,
	EnumEnd(Key)

public:

	static void translateQtEvent(const QEvent* evt, /*out*/EditorInputEvent& userEvt);

public:

	bool isCtrlActive() const { return (modifier & KeyModifier::Ctrl) != 0; }
	bool isShiftActive() const { return (modifier & KeyModifier::Shift) != 0; }
	bool isAltActive() const { return (modifier & KeyModifier::Alt) != 0; }

public:

	uint64 widgetUID;
	EventType eventType;
	uint32 button;    // mouse button or keyboard key
	uint32 modifier;  // keyboard modifier state flag
	uint32 mouseX;
	uint32 mouseY;


};

