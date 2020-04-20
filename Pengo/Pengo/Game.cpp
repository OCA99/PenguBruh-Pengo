#include "Game.h"
#include "Player.h"
#include "NormalBlock.h"
#include "Diamond.h"
#include "Blob.h"
#include "WallHorizontal.h"
#include "WallVertical.h"
#include "MenuBackground.h"
#include "Credits.h"


SDL_Renderer* Game::renderer = nullptr;
int Game::scale = 1;
bool Game::KEYS[322];
bool Game::godMode = false;

StateMachine <std::string, Scene*>* Game::sceneManager = nullptr;

Game::Game() {
	prefabs = new TypeMap<GameObject>();
	prefabs->registerType<Player>("player");
	prefabs->registerType<NormalBlock>("block");
	prefabs->registerType<Diamond>("diamond");
	prefabs->registerType<Blob>("blob");
	prefabs->registerType<WallHorizontal>("wall_hor");
	prefabs->registerType<WallVertical>("wall_vert");
	prefabs->registerType<MenuBackground>("menu_background");
	prefabs->registerType<Credits>("credits");
}

Game::~Game() {

}

void Game::init(const char* title, int x, int y, int _scale, Uint32 flags) {

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "SDL system initialized" << std::endl;
	}
	else {
		std::cout << "Could not initialize SDL" << std::endl;
		return;
	}

	scale = _scale;
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

	std::fill_n(KEYS, 322, false);

	CSV* data = readCSV("assets/scenes/scenes.txt");
	std::map<std::string, Scene*>* scenes = Scene::CreateScenesFromCSV(data, prefabs);
	sceneManager = new StateMachine <std::string, Scene*>(scenes);
	
	loadScene("credits");
	
}

void Game::handleFKeys(int k) {
	if (canChangeDebug) {
		if (k == 1073741882) {
			godMode = !godMode;
		}
		canChangeDebug = false;
	}
	else {
		canChangeDebug = true;
	}
}

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	SDL_Keycode key = NULL;
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYDOWN:
		key = event.key.keysym.sym;
		handleFKeys(key);
		if (key < 0 || key > 321) break;
		KEYS[key] = true;
		break;
	case SDL_KEYUP:
		key = event.key.keysym.sym;
		handleFKeys(key);
		if (key < 0 || key > 321) break;
		KEYS[key] = false;
		break;
	default:
		break;
	}
}


void Game::update() {
	sceneManager->getCurrentValue()->update();
}

void Game::render() {
	SDL_RenderClear(renderer);
	// Render objects
	sceneManager->getCurrentValue()->render();
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	sceneManager->getCurrentValue()->clean();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Clean up done" << std::endl;
}

void Game::loadScene(std::string name)
{
	sceneManager->setCurrentState(name);
	Scene* s = sceneManager->getCurrentValue();
	
	s->init();
}

void Game::changeScene(std::string name)
{
	Scene* current = sceneManager->getCurrentValue();
	current->clean();

	loadScene(name);

}