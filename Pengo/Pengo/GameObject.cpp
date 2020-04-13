#include "GameObject.h"

GameObject::GameObject()
{
	animation = nullptr;
	gridPosition = Vec2i(0, 0);
	position = Vec2f(0, 0);
}

GameObject::~GameObject()
{}

void GameObject::init()
{
	//std::cout << "Initialized" << std::endl;
}

void GameObject::update()
{
	//std::cout << "Updated" << std::endl;
}

void GameObject::render()
{
	if (!animation) return;
	animation->step();
	SDL_Rect* frame = animation->getFrame();
	SDL_Rect target;
	target.x = 64;
	target.y = 64;
	target.w = 16 * Game::scale;
	target.h = 16 * Game::scale;
	SDL_RenderCopy(Game::renderer, animation->source, frame, &target);
}

void GameObject::clean()
{
	//std::cout << "Cleaned" << std::endl;
}