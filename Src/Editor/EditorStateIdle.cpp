#include "EditorStateIdle.h"

#include "Assist/ObjectUID.h"
#include "Assist/Vector3.hpp"
#include "Assist/Point2.h"

#include "Editor/Editor.h"
#include "Editor/EditorStateCameraOrbit.h"


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
		if (evt.button == EditorInputEvent::MouseButton::Right)
		{
			// initiate camera orbit
			ObjectUID camUid = Editor::getInstance()->getMainCamera();
			Vector3 center = Vector3::ZERO; // TODO
			Point2 cursorPos = Point2(evt.mouseX, evt.mouseY);
			Editor::getInstance()->changeState(new EditorStateCameraOrbit(camUid, center, cursorPos));
		}
	}
}
