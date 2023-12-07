#include <iostream>
#include "engine.h"


int main(int argc, char* argv[])
{
	Engine* engine = Engine::GetInstance();
	engine->init("Test", 200, 200, argc, argv);
	while (engine->isRunning()) {
		cout << "engine is running..." << endl;
	}
	return 0;
}

