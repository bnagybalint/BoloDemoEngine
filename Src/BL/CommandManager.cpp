#include "CommandManager.h"

#include "BL/Command.h"

DEFINE_SINGLETON_IMPL(CommandManager);

CommandManager::CommandManager()
	: mLock()
	, mCommands()
{
}


CommandManager::~CommandManager()
{
	mLock.lock();
	for (int i = 0; i < mCommands.size(); i++)
	{
		delete mCommands[i]; mCommands[i] = NULL;
	}
	mCommands.clear();
	mLock.release();
}

void CommandManager::addCommand(Command* cmd)
{
	mLock.lock();
	mCommands.append(cmd);
	mLock.release();
}

void CommandManager::processCommands()
{
	mLock.lock();
	int numCommands = mCommands.size();
	mLock.release();

	for (int i = 0; i < numCommands; i++)
	{
		mLock.lock();
		Command* cmd = mCommands[i];
		mLock.release();

		cmd->execute();

		Command::ResultCode sc = cmd->getResultCode();
	}

	mLock.lock();
	for (int i = 0; i < numCommands; i++)
	{
		delete mCommands[i]; mCommands[i] = NULL;
	}
	mCommands.eRemoveHead(numCommands);
	mLock.release();
}
