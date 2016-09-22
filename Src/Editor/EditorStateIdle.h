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

	//virtual void enterState() override; // unused
	//virtual void leaveState() override; // unused
};

