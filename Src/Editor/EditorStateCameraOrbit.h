#pragma once

#include "Assist/Common.h"

#include "Assist/ObjectUID.h"
#include "Assist/Point2.h" 
#include "Assist/Vector3.hpp"
#include "Assist/Transform.hpp"

#include "Editor/EditorState.h"

class EditorStateCameraOrbit : public EditorState
{
public:

	// TODO not nice: cursorPosAtStart, should be queried from some mouse manager
	EditorStateCameraOrbit(const ObjectUID& cameraUid, const Vector3& orbitCenter, const Point2& cursorPosAtStart);
	DISABLE_COPY(EditorStateCameraOrbit);
	virtual ~EditorStateCameraOrbit();

public:

	void receiveInputEvent(const EditorInputEvent& evt) override;

	void enterState() override;
	//void leaveState() override; // unused

private:

	void calculateCameraTransform(const Point2& cursorPosition, /*out*/Transform& newTransfrom);

private:

	ObjectUID mCameraUid;
	Vector3   mOrbitCenter;

	Transform mInitialCameraTransform;
	Point2    mInitialCursorPosition;

	Vector3   mOrbitCenterInCameraLocal;
};

