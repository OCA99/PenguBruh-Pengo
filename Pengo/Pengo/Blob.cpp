#include "Blob.h"

Blob::Blob() : GameObject::GameObject() {
	construct();
}

Blob::Blob(Vec2i _position) : GameObject::GameObject(_position) {
	construct();
}

Blob::~Blob() {

}

void Blob::update() {
	GameObject::update();
	animation = animator->getCurrentValue();
	move();
}

void Blob::construct() {
	SDL_Texture* sprites = TextureManager::LoadTexture("assets/sprites/pengos.png");
	std::map<BlobAnimations, Animation*>* states = new std::map<BlobAnimations, Animation*>();
	SDL_Rect rect;
	rect.x = 128;
	rect.y = 128;
	rect.w = 96;
	rect.h = 16;
	Animation* spawn = new Animation(sprites, &rect, 1, 6, 15, 1, [&] { (*animator).setCurrentState(BlobAnimations::WalkDown); });
	(*states)[BlobAnimations::Spawn] = spawn;
	rect.y = 144;
	rect.w = 32;
	Animation* down = new Animation(sprites, &rect, 1, 2, 15, 1, nullptr);
	(*states)[BlobAnimations::WalkDown] = down;
	rect.x = 160;
	Animation* left = new Animation(sprites, &rect, 1, 2, 15, 1, nullptr);
	(*states)[BlobAnimations::WalkLeft] = left;
	rect.x = 176;
	Animation* up = new Animation(sprites, &rect, 1, 2, 15, 1, nullptr);
	(*states)[BlobAnimations::WalkUp] = up;
	rect.x = 192;
	Animation* right = new Animation(sprites, &rect, 1, 2, 15, 1, nullptr);
	(*states)[BlobAnimations::WalkRight] = right;
	rect.x = 1024;
	rect.y = 0;
	rect.w = 16;
	Animation* empty = new Animation(sprites, &rect, 1, 2, 15, 1, nullptr);
	(*states)[BlobAnimations::Empty] = empty;
	animator = new StateMachine<BlobAnimations, Animation*>(states);
	animator->setCurrentState(BlobAnimations::Spawn);
	type = 4;
	speed = 2;
}

void Blob::pushed(GameObject* origin) {
	std::cout << "Blob function called" << std::endl;
	if (gridPosition.y < origin->gridPosition.y) {
		if (!gridManager->canMoveToPosition(Vec2i(gridPosition.x, gridPosition.y - 1)))
		{
			destroy();
		}
		else
		{
			direction = Directions::Up;
			std::cout << "Blob directioned up" << std::endl;
		}
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

void Blob::destroy() {
	//animator->setCurrentState(BlockAnimations::Breaking);
	std::vector<GameObject*>* cell = gridManager->getCell(gridPosition.x, gridPosition.y);
	cell->erase(std::remove(cell->begin(), cell->end(), this), cell->end());
	animator->setCurrentState(BlobAnimations::Empty);
	std::cout << "Tontito destroyed" << std::endl;
	//needs delay to do animation
	//animator->setCurrentState(BlockAnimations::Empty);
}

void Blob::move() {
	std::cout << "MOVE" << std::endl;
	if (moving) return;
	std::cout << (int) direction << std::endl;
	switch (direction) {
	case Directions::Up:
		std::cout << "Direction Up" << std::endl;
		if (gridManager->canMoveToPosition(Vec2i(gridPosition.x, gridPosition.y - 1)))
		{
			moveToGridPosition(Vec2i(gridPosition.x, gridPosition.y - 1));
			std::cout << "CAN MOVE" << std::endl;
		}
		else
		{
			destroy();
			std::cout << "DESTROYED" << std::endl;
		}

		break;
	case Directions::Left:
		if (gridManager->canMoveToPosition(Vec2i(gridPosition.x - 1, gridPosition.y)))
			moveToGridPosition(Vec2i(gridPosition.x - 1, gridPosition.y));
		else
			destroy();
		break;
	case Directions::Down:
		if (gridManager->canMoveToPosition(Vec2i(gridPosition.x, gridPosition.y + 1)))
			moveToGridPosition(Vec2i(gridPosition.x, gridPosition.y + 1));
		else
			destroy();
		break;
	case Directions::Right:
		if (gridManager->canMoveToPosition(Vec2i(gridPosition.x + 1, gridPosition.y)))
			moveToGridPosition(Vec2i(gridPosition.x + 1, gridPosition.y));
		else
			destroy();
		break;
	default:
		break;
	}
}