#include "Game.h"

SDL_Renderer* Game::renderer = nullptr;
Game::Game() {
	
}

Game::~Game() {

}

void Game::init(const char* title, int x, int y, int scale, Uint32 flags) {

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "SDL system initialized" << std::endl;
	}
	else {
		std::cout << "Could not initialize SDL" << std::endl;
		return;
	}

	window = SDL_CreateWindow(title, x, y, size.x * scale, size.y * scale, flags);
	if (window) {
		std::cout << "Window created" << std::endl;
	}
	else {
		std::cout << "Could not create window" << std::endl;
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer) {
		std::cout << "Renderer created" << std::endl;
	}
	else {
		std::cout << "Could not create renderer" << std::endl;
		return;
	}

	isRunning = true;
}

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update() {

	currentScene->update();
	
}

void Game::render() {
	SDL_RenderClear(renderer);
	// Render objects
	currentScene->render();

	SDL_RenderPresent(renderer);


}

void Game::clean() {
	currentScene->clean();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Clean up done" << std::endl;
}

void Game::loadScene(Scene* s)
{
	if (currentScene) currentScene->clean();
	
	currentScene = s;
	currentScene->init();
}