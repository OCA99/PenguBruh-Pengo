#include "Pengo.h"

Pengo::Pengo() {
	SDL_Texture* sprites = TextureManager::LoadTexture("assets/sprites/pengos.png");
	std::map<PengoAnimations, Animation*>* states = new std::map<PengoAnimations, Animation*>();
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = 32;
	rect.h = 16;
	Animation* down = new Animation(sprites, &rect, 1, 2, 15);
	(*states)[PengoAnimations::WalkDown] = down;
	rect.x = 32;
	Animation* left = new Animation(sprites, &rect, 1, 2, 15);
	(*states)[PengoAnimations::WalkLeft] = left;
	rect.x = 64;
	Animation* up = new Animation(sprites, &rect, 1, 2, 15);
	(*states)[PengoAnimations::WalkUp] = up;
	rect.x = 96;
	Animation* right = new Animation(sprites, &rect, 1, 2, 15);
	(*states)[PengoAnimations::WalkRight] = right;
	animator = new StateMachine<PengoAnimations, Animation*>(states);
	gridPosition = Vec2i(0, 0);
	position = Vec2f(0, 0);
	animator->setCurrentState(PengoAnimations::WalkDown);
	pressedKeys = new std::vector<SDL_Keycode>();
	direction = Directions::Down;
}

Pengo::~Pengo() {

}

void Pengo::update() {
	animation = animator->getCurrentValue();
	if (Game::KEYS[SDLK_w]) {
		if (std::find(pressedKeys->begin(), pressedKeys->end(), SDLK_w) == pressedKeys->end())
			pressedKeys->push_back(SDLK_w);
	}
	if (Game::KEYS[SDLK_a]) {
		if (std::find(pressedKeys->begin(), pressedKeys->end(), SDLK_a) == pressedKeys->end())
			pressedKeys->push_back(SDLK_a);
	}
	if (Game::KEYS[SDLK_s]) {
		if (std::find(pressedKeys->begin(), pressedKeys->end(), SDLK_s) == pressedKeys->end())
			pressedKeys->push_back(SDLK_s);
	}
	if (Game::KEYS[SDLK_d]) {
		if (std::find(pressedKeys->begin(), pressedKeys->end(), SDLK_d) == pressedKeys->end())
			pressedKeys->push_back(SDLK_d);
	}
	if (!pressedKeys->empty()) {
		switch ((*pressedKeys)[pressedKeys->size() - 1])
		{
		case SDLK_w:
			direction = Directions::Up;
			animator->setCurrentState(PengoAnimations::WalkUp);
			break;
		case SDLK_a:
			direction = Directions::Left;
			animator->setCurrentState(PengoAnimations::WalkLeft);
			break;
		case SDLK_s:
			direction = Directions::Down;
			animator->setCurrentState(PengoAnimations::WalkDown);
			break;
		case SDLK_d:
			direction = Directions::Right;
			animator->setCurrentState(PengoAnimations::WalkRight);
			break;
		default:
			break;
		}
	}
	for (SDL_Keycode k : *pressedKeys) {
		if (!Game::KEYS[k])
			pressedKeys->erase(std::remove(pressedKeys->begin(), pressedKeys->end(), k), pressedKeys->end());
	}
}