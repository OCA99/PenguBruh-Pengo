#include "Player.h"

Player::Player() : Pengo::Pengo() {
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
	if (!pressedKeys->empty() && !pushing) {
		switch ((*pressedKeys)[pressedKeys->size() - 1])
		{
		case SDLK_w:
			if (!moving) {
				direction = Directions::Up;
				if (gridManager->canMoveToPosition(Vec2i(gridPosition.x, gridPosition.y - 1)))
				{
					moveToGridPosition(Vec2i(gridPosition.x, gridPosition.y - 1));
					moving = true;
				}
			}
			break;
		case SDLK_a:
			if (!moving) {
				direction = Directions::Left;
				if (gridManager->canMoveToPosition(Vec2i(gridPosition.x - 1, gridPosition.y)))
				{
					moveToGridPosition(Vec2i(gridPosition.x - 1, gridPosition.y));
					moving = true;
				}
			}
			break;
		case SDLK_s:
			if (!moving) {
				direction = Directions::Down;
				if (gridManager->canMoveToPosition(Vec2i(gridPosition.x, gridPosition.y + 1)))
				{
					moveToGridPosition(Vec2i(gridPosition.x, gridPosition.y + 1));
					moving = true;
				}
			}
			break;
		case SDLK_d:
			if (!moving) {
				direction = Directions::Right;
				if (gridManager->canMoveToPosition(Vec2i(gridPosition.x + 1, gridPosition.y)))
				{
					moveToGridPosition(Vec2i(gridPosition.x + 1, gridPosition.y));
					moving = true;
				}
			}
			break;
		default:
			break;
		}
	}
	for (SDL_Keycode k : *pressedKeys) {
		if (!Game::KEYS[k])
			pressedKeys->erase(std::remove(pressedKeys->begin(), pressedKeys->end(), k), pressedKeys->end());
	}
	if (!pushing) {
		switch (direction) {
		case Directions::Up:
			animator->setCurrentState(PengoAnimations::WalkUp);
			break;
		case Directions::Left:
			animator->setCurrentState(PengoAnimations::WalkLeft);
			break;
		case Directions::Down:
			animator->setCurrentState(PengoAnimations::WalkDown);
			break;
		case Directions::Right:
			animator->setCurrentState(PengoAnimations::WalkRight);
			break;
		default:
			break;
		}
		if (moving) {
			animator->getCurrentValue()->play();
		}
		else {
			animator->getCurrentValue()->pause();
		}
	}
	if (!moving)
		if (checkForEnemy() && !Game::godMode) die();
	std::cout << moving << std::endl;
	if (Game::KEYS[SDLK_SPACE] && !moving && !pushing) {
		push();
	}
}

void Player::die() {
	animator->setCurrentState(PengoAnimations::Die);
}

void Player::push() {
	GameObject* block_type = nullptr;
	Vec2i pos = Vec2i();
	switch (direction) {
	case Directions::Up:
		pos = Vec2i(gridPosition.x, gridPosition.y - 1);
		if (!gridManager->isPartOfGrid(pos)) break;
		block_type = gridManager->getAnyBlock(pos);
		if (block_type)
		{
			animator->setCurrentState(PengoAnimations::PushUp);
			animator->getCurrentValue()->play();
		}
		break;
	case Directions::Left:
		pos = Vec2i(gridPosition.x - 1, gridPosition.y);
		if (!gridManager->isPartOfGrid(pos)) break;
		block_type = gridManager->getAnyBlock(pos);
		if (block_type)
		{
			animator->setCurrentState(PengoAnimations::PushLeft);
			animator->getCurrentValue()->play();
		}
		break;
	case Directions::Down:
		pos = Vec2i(gridPosition.x, gridPosition.y + 1);
		if (!gridManager->isPartOfGrid(pos)) break;
		block_type = gridManager->getAnyBlock(pos);
		if (block_type)
		{
			animator->setCurrentState(PengoAnimations::PushDown);
			animator->getCurrentValue()->play();
		}
		break;
	case Directions::Right:
		pos = Vec2i(gridPosition.x + 1, gridPosition.y);
		if (!gridManager->isPartOfGrid(pos)) break;
		block_type = gridManager->getAnyBlock(pos);
		if (block_type)
		{
			animator->setCurrentState(PengoAnimations::PushRight);
			animator->getCurrentValue()->play();
		}
		break;
	}
	if (!block_type) return;
	pushing = true;
	block_type->pushed(this);
}

bool Player::checkForEnemy() {
	if (gridManager->containsObject(gridManager->pixelPositionToGrid(position), 4)) return true;
	return false;
}

void Player::construct() {
	pressedKeys = new std::vector<SDL_Keycode>();
	direction = Directions::Down;
	type = 1;
	speed = 1;
}