#pragma once

#include "Assist/Common.h"
#include "Assist/Array.h"
#include "Assist/Mutex.h"

class Command;

class CommandManager
{
public:

	DECLARE_SINGLETON_HEADER(CommandManager);

public:

	// Commands are deferred execution units, that are used to defer work to a later point in time
	// NOTE: this is reserved for Editor-Application communication, Application objects should not create and issue Commands.
	// NOTE: ownership of the command object is transferred, Application object will release the command object.
	void addCommand(Command* cmd);

	// Process commands accumulated since last time this function was called
	void processCommands();

private:

	CommandManager();
	~CommandManager();

private:

	Mutex mLock;
	Array<Command*> mCommands;
};

