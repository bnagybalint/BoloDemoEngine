#include "EditorStateIdle.h"


EditorStateIdle::EditorStateIdle()
{
}

EditorStateIdle::~EditorStateIdle()
{
}

void EditorStateIdle::receiveInputEvent(const EditorInputEvent& evt)
{
	if (evt.eventType == EditorInputEvent::EventType::MouseDown)
	{
		if (evt.button == EditorInputEvent::MouseButton::Left)
		{
			// NOP
		}
		else if (evt.button == EditorInputEvent::MouseButton::Middle)
		{
			// TODO FIXME
		}
		else if (evt.button == EditorInputEvent::MouseButton::Middle)
		{
			// NOP
		}
		else Unimplemented();
	}
}
