#pragma once

#include <SDL.h>

class Game {
public:
	Game();
	~Game();

	int init(const char* title, int x, int y, int w, int h, Uint32 flags);
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