#include "engine.h"

int main(int argc, char *argv[]) {
  // Get the instance of the engine
  Engine &engine = Engine::getInstance();

  // Initialize the engine
  engine.initialize(argc, argv);

  // Run the engine
  engine.run();

  return 0;
}
