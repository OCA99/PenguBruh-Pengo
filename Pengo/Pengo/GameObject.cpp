#include "GameObject.h"

GameObject::GameObject()
{
	animation = nullptr;
	position = Vec2i(0, 0);
}

GameObject::GameObject(Vec2i _position)
{
	animation = nullptr;
	position = _position;
}

GameObject::~GameObject()
{
	ownerScene->objects.erase(std::remove(ownerScene->objects.begin(), ownerScene->objects.end(), this), ownerScene->objects.end());
}

void GameObject::init()
{
}

void GameObject::update() {
	stepToTargetPosition();
}

void GameObject::stepToTargetPosition() {
	if (position.x != targetPosition.x) {
		moving = true;
		if (position.x < targetPosition.x)
			position = Vec2i(position.x + speed, position.y);
		if (position.x > targetPosition.x)
			position = Vec2i(position.x - speed, position.y);
	}
	if (position.y != targetPosition.y) {
		moving = true;
		if (position.y < targetPosition.y)
			position = Vec2i(position.x, position.y + speed);
		if (position.y > targetPosition.y)
			position = Vec2i(position.x, position.y - speed);
	}
	if (position.x == targetPosition.x && position.y == targetPosition.y) {
		moving = false;
	}
}

bool GameObject::isInTargetPosition() {
	return gridPosition.x == targetPosition.x && gridPosition.y == targetPosition.y;
}

void GameObject::render()
{
	if (!animation) {
		return;
	}
	animation->step();
	SDL_Rect* frame = animation->getFrame();
	SDL_Rect target;
	target.x = position.x * Game::scale;
	target.y = position.y * Game::scale;
	target.w = frame->w * Game::scale;
	target.h = frame->h * Game::scale;
	SDL_RenderCopy(Game::renderer, animation->source, frame, &target);
}

void GameObject::moveToGridPosition(Vec2i newPosition) {
	std::vector<GameObject*>* cell = gridManager->getCell(gridPosition.x, gridPosition.y);
	cell->erase(std::remove(cell->begin(), cell->end(), this), cell->end());
	gridPosition = newPosition;
	gridManager->getCell(newPosition.x, newPosition.y)->push_back(this);
	targetPosition = gridManager->gridToPixelPosition(newPosition);
}

void GameObject::clean()
{
	//delete animation;
}