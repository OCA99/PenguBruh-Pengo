#include "Player.h"

Player::Player() : Pengo::Pengo() {
	std::cout << "Constructing player" << std::endl;
	construct();
}

Player::Player(Vec2i _position) : Pengo::Pengo(_position) {
	construct();
}

Player::~Player() {

}

void Player::update() {
	Pengo::update();
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
			if (!moving) {
				if (gridManager->canMoveToPosition(Vec2i(gridPosition.x, gridPosition.y - 1)))
					moveToGridPosition(Vec2i(gridPosition.x, gridPosition.y - 1));
			}
			break;
		case SDLK_a:

			break;
		case SDLK_s:
			
			break;
		case SDLK_d:
			
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

void Player::construct() {
	pressedKeys = new std::vector<SDL_Keycode>();
	direction = Directions::Down;
	type = 1;
	speed = 2;
}