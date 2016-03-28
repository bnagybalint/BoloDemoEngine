#include "Command.h"


Command::Command()
	: mStatus(ResultCode::NotStarted)
{
}

Command::~Command()
{
}

void Command::execute()
{
	executeCommand();
	AssertMsg(mStatus != ResultCode::NotStarted, "Command did not call any termination-indicator methods (finished, cancel or fail)");
}

void Command::finished()
{
	AssertMsg(mStatus == ResultCode::NotStarted, "Trying to change command result from an already set value.");
	mStatus = ResultCode::Finished;
}
void Command::cancel()
{
	AssertMsg(mStatus == ResultCode::NotStarted, "Trying to change command result from an already set value.");
	mStatus = ResultCode::Canceled;
	bool cancelOk = cancelCommand();

	if (!cancelOk)
		mStatus = ResultCode::Fatal;
}
void Command::fail()
{
	AssertMsg(mStatus == ResultCode::NotStarted, "Trying to change command result from an already set value.");
	mStatus = ResultCode::Failed;
}

bool Command::cancelCommand()
{
	// nop
	return true;
}
