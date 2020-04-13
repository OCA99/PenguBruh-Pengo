#include "GameObject.h"

GameObject::GameObject()
{
	texture = nullptr;
	gridPosition = Vec2i(0, 0);
	position = Vec2f(0, 0);
}

GameObject::GameObject(const char* texturePath, int x, int y)
{
	texture = TextureManager::LoadTexture(texturePath, Game::renderer);
	gridPosition = Vec2i(x, y);
	position = Vec2f(x, y);
}

GameObject::GameObject(const char* texturePath, Vec2i _gridPosition) {
	texture = TextureManager::LoadTexture(texturePath, Game::renderer);
	gridPosition = _gridPosition;
	position = Vec2f(_gridPosition.x, _gridPosition.y);
}

GameObject::~GameObject()
{}

void GameObject::init()
{
	std::cout << "Initialized" << std::endl;
}

void GameObject::update()
{
	std::cout << "Updated" << std::endl;
}

void GameObject::render()
{
	std::cout << "Rendered" << std::endl;
}

void GameObject::clean()
{
	std::cout << "Cleaned" << std::endl;
}