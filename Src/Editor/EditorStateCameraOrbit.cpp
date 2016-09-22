#include "EditorStateCameraOrbit.h"

#include "Assist/PropertyOwner.h"

#include "Editor/Editor.h"
#include "Editor/EditorStateIdle.h"

#include "BL/DisplayCamera.h"
#include "BL/CommandManager.h"
#include "BL/PropertyChangeCommand.h"


EditorStateCameraOrbit::EditorStateCameraOrbit(const ObjectUID& cameraUid, const Vector3& orbitCenter, const Point2& cursorPosAtStart)
	: mCameraUid(cameraUid)
	, mOrbitCenter(orbitCenter)
	, mInitialCameraTransform(Transform::IDENTITY)
	, mInitialCursorPosition(cursorPosAtStart)
	, mOrbitCenterInCameraLocal(Vector3::ZERO)
{
}

EditorStateCameraOrbit::~EditorStateCameraOrbit()
{
}

void EditorStateCameraOrbit::receiveInputEvent(const EditorInputEvent& evt)
{
	if (evt.eventType == EditorInputEvent::EventType::MouseMove)
	{
		Transform newCamTransform;
		calculateCameraTransform(Point2(evt.mouseX, evt.mouseY), newCamTransform);

		CommandManager::getInstance()->addCommand(new PropertyChangeCommand<Vector3>(mCameraUid, "position", newCamTransform.getPosition()));
		CommandManager::getInstance()->addCommand(new PropertyChangeCommand<Quaternion>(mCameraUid, "orientation", newCamTransform.getOrientation()));
	}
	else if (evt.eventType == EditorInputEvent::EventType::MouseUp)
	{
		if (evt.button == EditorInputEvent::MouseButton::Right)
		{
			Editor::getInstance()->changeState(new EditorStateIdle());
		}
	}
}

void EditorStateCameraOrbit::enterState()
{
	PropertyOwner* propOwner = PropertyOwner::lockPropertyOwner(mCameraUid);

	DisplayCamera* camera = PropertyOwner::cast<DisplayCamera>(propOwner);
	Assert(camera);
	mInitialCameraTransform = Transform(camera->position, camera->orientation);
	mOrbitCenterInCameraLocal = Transform::inverse(mInitialCameraTransform).transform(mOrbitCenter);

	PropertyOwner::unlockPropertyOwner(propOwner); propOwner = NULL;
}

void EditorStateCameraOrbit::calculateCameraTransform(const Point2& cursorPosition, /*out*/Transform& newTransfrom)
{
	// TODO use as environment settings?
	const float MouseSensitivityX = Math::Deg2Rad(360.0f); // radians rotated per window width
	const float MouseSensitivityY = Math::Deg2Rad(90.0f); // radians rotated per window height

	float radsx = MouseSensitivityX * float(cursorPosition.x - mInitialCursorPosition.x) / 800; // TODO use actual window/widget dimensions
	float radsy = MouseSensitivityY * float(cursorPosition.y - mInitialCursorPosition.y) / 600; // TODO use actual window/widget dimensions

	Quaternion qx = Quaternion::createFromAxisAngle(-radsx, Vector3::UNIT_Y);
	Quaternion qy = Quaternion::createFromAxisAngle(-radsy, Vector3::UNIT_X);

	// FIXME not using y axis for now...
	Quaternion qnew = qx * mInitialCameraTransform.getOrientation();
	Vector3    pnew = -(qnew * mOrbitCenterInCameraLocal);

	newTransfrom.setOrientation(qnew);
	newTransfrom.setPosition(pnew);
}
