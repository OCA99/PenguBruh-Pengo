#include "Diamond.h"

Diamond::Diamond() : GameObject::GameObject() {
	construct();
}

Diamond::Diamond(Vec2i _position) : GameObject::GameObject(_position) {
	construct();
}

Diamond::~Diamond() {

}

void Diamond::update() {
	GameObject::update();
	animation = animator->getCurrentValue();
	move();
}

void Diamond::move() {
	if (moving) return;
	switch (direction) {
	case Directions::Up:
		if (gridManager->canMoveToPosition(Vec2i(gridPosition.x, gridPosition.y - 1)))
			moveToGridPosition(Vec2i(gridPosition.x, gridPosition.y - 1));
		else
			direction = Directions::Stopped;
		break;
	case Directions::Left:
		if (gridManager->canMoveToPosition(Vec2i(gridPosition.x - 1, gridPosition.y)))
			moveToGridPosition(Vec2i(gridPosition.x - 1, gridPosition.y));
		else
			direction = Directions::Stopped;
		break;
	case Directions::Down:
		if (gridManager->canMoveToPosition(Vec2i(gridPosition.x, gridPosition.y + 1)))
			moveToGridPosition(Vec2i(gridPosition.x, gridPosition.y + 1));
		else
			direction = Directions::Stopped;
		break;
	case Directions::Right:
		if (gridManager->canMoveToPosition(Vec2i(gridPosition.x + 1, gridPosition.y)))
			moveToGridPosition(Vec2i(gridPosition.x + 1, gridPosition.y));
		else
			direction = Directions::Stopped;
		break;
	default:
		break;
	}
}



void Diamond::destroy() {
	// Define object destroy
}

void Diamond::pushed(GameObject* origin) {
	if (gridPosition.x > origin->gridPosition.x) {
		direction = Directions::Right;
	}
	if (gridPosition.x < origin->gridPosition.x) {
		direction = Directions::Left;
	}
	if (gridPosition.y > origin->gridPosition.y) {
		direction = Directions::Down;
	}
	if (gridPosition.y < origin->gridPosition.y) {
		direction = Directions::Up;
	}
}


void Diamond::construct() {
	SDL_Texture* sprites = TextureManager::LoadTexture("assets/sprites/Stages.png");
	std::map<DiamondAnimations, Animation*>* states = new std::map<DiamondAnimations, Animation*>();
	SDL_Rect rect;
	rect.x = 708;
	rect.y = 16;
	rect.w = 16;
	rect.h = 16;
	Animation* normal = new Animation(sprites, &rect, 1, 1, 1, 1, nullptr);
	(*states)[DiamondAnimations::Normal] = normal;
	animator = new StateMachine<DiamondAnimations, Animation*>(states);
	animator->setCurrentState(DiamondAnimations::Normal);
	type = 3;
	speed = 2;
}