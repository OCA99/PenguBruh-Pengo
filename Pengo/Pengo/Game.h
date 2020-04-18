#pragma once

class GameObject;
class Scene;
class Game;
class Animation;

#include <iostream>
#include <algorithm>
#include <SDL.h>
#include "Vec2.h"
#include "Scene.h"
#include "CSVReader.h"
#include "TypeMap.h"

class Game {
public:
	Game();
	~Game();

	void init(const char* title, int x, int y, int _scale, Uint32 flags);
	void handleEvents();
	void handleFKeys(SDL_Keycode k);
	void update();
	void render();
	void clean();

	void loadScene(Scene* s);

	bool running() { return isRunning; };

	static SDL_Renderer* renderer;
	static int scale;
	static bool KEYS[322];
	static bool godMode;
private:
	bool isRunning = false;
	SDL_Window* window = nullptr;
	const Vec2i size = Vec2i(224,288);

	Scene* currentScene = nullptr;

	TypeMap<GameObject>* prefabs;

	bool canChangeDebug = true;
};