#pragma once

#include "Assist/Common.h"

#include "Editor/EditorState.h"

class EditorStateIdle : public EditorState
{
public:

	EditorStateIdle();
	DISABLE_COPY(EditorStateIdle);
	virtual ~EditorStateIdle();

public:

	void receiveInputEvent(const EditorInputEvent& evt) override;

	//virtual void enterState() {} // unused
	//virtual void leaveState() {} // unused
};

