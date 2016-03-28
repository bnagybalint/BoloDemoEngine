#pragma once

#include "Assist/Common.h"

class Command
{
public:

	EnumBegin(ResultCode, NotStarted)
		NotStarted,       // not executed
		Finished,         // successful
		Canceled,         // command was canceled before it could be completed
		Failed,           // failed to execute because Model refused operation
		Fatal,            // unrecoverable error occurred during execution
	EnumEnd(ResultCode)

public:

	virtual ~Command();
	
	void execute();

	ResultCode getResultCode() const { return mStatus; }

protected:

	Command();

	// Signal that the command has finished execution. This is the normal behaviour.
	void ok();
	// Signal that the command should be canceled. If this function is called, cancelCommand() will be called to clean-up/rollback the command.
	void cancel();
	// Signal that the command has failed to execute due to some reason.
	void fail();

private:

	// Execute the command. This method must be implemented in the derived classes.
	virtual void executeCommand() = 0;
	// Do cleanup/rollback operations after command has been canceled.
	// Return true if cleanup has been successful, false otherwise.
	virtual bool cancelCommand();

private:

	ResultCode mStatus;
};

