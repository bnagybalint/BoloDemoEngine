#include "ObjectUID.h"

#include "Assist/UIDGenerator.h"

ObjectUID GenerateObjectUID()
{
	return UIDGenerator::getInstance()->generate();
}
