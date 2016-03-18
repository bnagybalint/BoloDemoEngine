#include "Application.h"

int main(int argc, char** argv)
{
	Application::createSingletonInstance();
	return Application::getInstance()->run(argc, argv);
}
