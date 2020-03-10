#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

class Game {
public:
	Game();
	~Game();

	void init(const char* title, int x, int y, int w, int h, Uint32 flags);
	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; };
private:
	bool isRunning = false;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
};