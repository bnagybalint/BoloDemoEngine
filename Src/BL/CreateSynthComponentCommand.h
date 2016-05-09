#pragma once

#include "Assist/Common.h"

#include "BL/Command.h"

#include "Assist/String.h"
#include "Assist/Vector2.h"

class CreateSynthComponentCommand : public Command
{
public:

	CreateSynthComponentCommand(const String& typeName, const Vector2& position);
	~CreateSynthComponentCommand();

	void executeCommand() override;

private:

	String mComponentTypeName;
	Vector2 mPosition;
};

