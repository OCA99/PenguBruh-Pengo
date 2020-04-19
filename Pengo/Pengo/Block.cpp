#include "Block.h"

Block::Block() : GameObject::GameObject() {
	construct();
}

Block::Block(Vec2i _position) : GameObject::GameObject(_position) {
	construct();
}

Block::~Block() {

}

void Block::update() {
	GameObject::update();
	animation = animator->getCurrentValue();
	move();
}

void Block::move() {
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

void Block::destroy() {
	animator->setCurrentState(BlockAnimations::Breaking);
	std::vector<GameObject*>* cell = gridManager->getCell(gridPosition.x, gridPosition.y);
	cell->erase(std::remove(cell->begin(), cell->end(), this), cell->end());
	//needs delay to do animation
	//animator->setCurrentState(BlockAnimations::Empty);
}

void Block::pushed(GameObject* origin) {
	if (gridPosition.y < origin->gridPosition.y) {
		if (!gridManager->canMoveToPosition(Vec2i(gridPosition.x, gridPosition.y - 1)))
		{
			Block::destroy();
		}
		direction = Directions::Up;
	}
	if (gridPosition.x < origin->gridPosition.x) {
		if (!gridManager->canMoveToPosition(Vec2i(gridPosition.x - 1, gridPosition.y)))
		{
			Block::destroy();
		}
		direction = Directions::Left;
	}
	if (gridPosition.y > origin->gridPosition.y) {
		if (!gridManager->canMoveToPosition(Vec2i(gridPosition.x, gridPosition.y + 1)))
		{
			Block::destroy();
		}
		direction = Directions::Down;
	}
	if (gridPosition.x > origin->gridPosition.x) {
		if (!gridManager->canMoveToPosition(Vec2i(gridPosition.x + 1, gridPosition.y))) {
			Block::destroy();
		}
		direction = Directions::Right;
	}
}


void Block::construct() {
	SDL_Texture* sprites = TextureManager::LoadTexture("assets/sprites/Stages.png");
	std::map<BlockAnimations, Animation*>* states = new std::map<BlockAnimations, Animation*>();
	SDL_Rect rect;
	rect.x = 708;
	rect.y = 0;
	rect.w = 16;
	rect.h = 16;
	Animation* normal = new Animation(sprites, &rect, 1, 1, 1, 1, nullptr);
	(*states)[BlockAnimations::Normal] = normal;
	rect.y = 48;
	rect.w = 144;
	Animation* breaking = new Animation(sprites, &rect, 1, 9, 8, 1, [&] { destroy(); });
	(*states)[BlockAnimations::Breaking] = breaking;
	animator = new StateMachine<BlockAnimations, Animation*>(states);
	animator->setCurrentState(BlockAnimations::Normal);
	type = 2;
	speed = 2;
}