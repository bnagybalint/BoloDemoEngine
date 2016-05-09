#include "CreateSynthComponentCommand.h"

#include "BL/Application.h"
#include "BL/SynthScene.h"
#include "BL/SynthComponent.h"
#include "BL/SynthComponentFactory.h"

#include "Audio/AudioComponent.h"


CreateSynthComponentCommand::CreateSynthComponentCommand(const String& typeName, const Vector2& position)
	: mComponentTypeName(typeName)
	, mPosition(position)
{
}

CreateSynthComponentCommand::~CreateSynthComponentCommand()
{
}

void CreateSynthComponentCommand::executeCommand()
{
	SynthScene* scene = Application::getInstance()->getSynthScene();

	SynthComponent* synthComp = SynthComponentFactory::getInstance()->createSynthComponent(mComponentTypeName, scene);
	scene->addObject(synthComp);

	finished();
}
