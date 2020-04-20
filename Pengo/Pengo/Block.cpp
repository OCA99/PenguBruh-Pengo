#include "Block.h"

Block::Block() : GameObject::GameObject() {
}

Block::Block(Vec2i _position) : GameObject::GameObject(_position) {
}

Block::~Block() {
	//std::cout << "block destructor" << std::endl;
}

void Block::update() {
	GameObject::update();
	animation = animator->getCurrentValue();
	move();
}

void Block::clean() {
	//delete animator;
	//GameObject::clean();
	animator->setCurrentState(BlockAnimations::Empty);
}

void Block::move() {
	if (moving) return;
	Vec2i nextpos = Vec2i();
	switch (direction) {
	case Directions::Up:
		nextpos = Vec2i(gridPosition.x, gridPosition.y - 1);
		if (gridManager->isPartOfGrid(nextpos) && gridManager->containsObject(nextpos, 4))
		{
			std::cout << "Bloque Empujado" << std::endl;
			gridManager->getAnyBlob(nextpos)->pushed(this);
		}
		if (gridManager->canMoveToPosition(nextpos))
			moveToGridPosition(nextpos);
		else
			direction = Directions::Stopped;
		break;
	case Directions::Left:
		nextpos = Vec2i(gridPosition.x - 1, gridPosition.y);
		if (gridManager->isPartOfGrid(nextpos) && gridManager->containsObject(nextpos, 4))
		{
			gridManager->getAnyBlob(nextpos)->pushed(this);
		}
		if (gridManager->canMoveToPosition(nextpos))
			moveToGridPosition(nextpos);
		else
			direction = Directions::Stopped;
		break;
	case Directions::Down:
		nextpos = Vec2i(gridPosition.x, gridPosition.y + 1);
		if (gridManager->isPartOfGrid(nextpos) && gridManager->containsObject(nextpos, 4))
		{
			gridManager->getAnyBlob(nextpos)->pushed(this);
		}
		if (gridManager->canMoveToPosition(nextpos))
			moveToGridPosition(nextpos);
		else
			direction = Directions::Stopped;
		break;
	case Directions::Right:
		nextpos = Vec2i(gridPosition.x + 1, gridPosition.y);
		if (gridManager->isPartOfGrid(nextpos) && gridManager->containsObject(nextpos, 4))
		{
			gridManager->getAnyBlob(nextpos)->pushed(this);
		}
		if (gridManager->canMoveToPosition(nextpos))
			moveToGridPosition(nextpos);
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
			destroy();
		}
		else
			direction = Directions::Up;
	}
	if (gridPosition.x < origin->gridPosition.x) {
		if (!gridManager->canMoveToPosition(Vec2i(gridPosition.x - 1, gridPosition.y)))
		{
			destroy();
		}
		else
			direction = Directions::Left;
	}
	if (gridPosition.y > origin->gridPosition.y) {
		if (!gridManager->canMoveToPosition(Vec2i(gridPosition.x, gridPosition.y + 1)))
		{
			destroy();
		}
		else
			direction = Directions::Down;
	}
	if (gridPosition.x > origin->gridPosition.x) {
		if (!gridManager->canMoveToPosition(Vec2i(gridPosition.x + 1, gridPosition.y)))
		{
			destroy();
		}
		else
			direction = Directions::Right;
	}
}