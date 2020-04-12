#pragma once

#include <iostream>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "Vec2.h"
#include "Scene.h"
#include "GameObject.h"

class Game {
public:
	Game();
	~Game();

	void init(const char* title, int x, int y, int scale, Uint32 flags);
	void handleEvents();
	void update();
	void render();
	void clean();

	void loadScene(Scene* s);

	bool running() { return isRunning; };

	static SDL_Renderer* renderer;
private:
	bool isRunning = false;
	SDL_Window* window = nullptr;
	const Vec2i size = Vec2i(224,288);

	Scene* currentScene = nullptr;
};