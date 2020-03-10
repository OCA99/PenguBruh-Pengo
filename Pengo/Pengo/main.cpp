#include "Game.h"

Game* game = nullptr;

int main(int argc, char* argv[]) {

	game = new Game();

	game->init("Pengo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 896, 1152, SDL_WINDOW_SHOWN);

	while (game->running()) {
		game->handleEvents();
		game->update();
		game->render();
	}

	game->clean();

	return 0;
}