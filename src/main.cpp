#include "game.h"

int main() {
  // Init srand
  srand(static_cast<unsigned>(time(NULL)));
  // Init Game engine
  Game game;

  // Game loop
  while (game.running()) {
    // Update
    game.update();

    // Render
    game.render();
  }
  return 0;
}
