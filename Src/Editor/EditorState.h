#pragma once

#include "Assist/Common.h"

#include "Editor/EditorInputEvent.h"

class EditorState
{
public:

	EditorState();
	DISABLE_COPY(EditorState);
	virtual ~EditorState();

public:

	// Handle input from the user (mouse/keyboard)
	virtual void receiveInputEvent(const EditorInputEvent& evt) = 0;

	virtual void enterState() {}
	virtual void leaveState() {}
};

