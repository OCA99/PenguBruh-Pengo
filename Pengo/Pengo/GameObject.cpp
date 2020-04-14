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
{}

void GameObject::init()
{
	//std::cout << "Initialized" << std::endl;
}

void GameObject::render()
{
	if (!animation) return;
	animation->step();
	SDL_Rect* frame = animation->getFrame();
	SDL_Rect target;
	target.x = position.x * Game::scale;
	target.y = position.y * Game::scale;
	target.w = frame->w * Game::scale;
	target.h = frame->h * Game::scale;
	SDL_RenderCopy(Game::renderer, animation->source, frame, &target);
}

void GameObject::clean()
{
	//std::cout << "Cleaned" << std::endl;
}