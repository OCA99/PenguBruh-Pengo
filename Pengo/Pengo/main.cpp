#include "Game.h"

Game* game = nullptr;

int main(int argc, char* argv[]) {

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint64 gameTicks;
	int frameTicks;

	game = new Game();

	game->init("Pengo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 448, 576, SDL_WINDOW_SHOWN);

	while (game->running()) {

		gameTicks = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTicks = SDL_GetTicks() - gameTicks;

		if (frameDelay > frameTicks) {
			SDL_Delay(frameDelay - frameTicks);
		}
	}

	game->clean();

	return 0;
}