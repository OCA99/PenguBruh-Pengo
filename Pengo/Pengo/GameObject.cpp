#include "GameObject.h"


GameObject::GameObject()
{}

GameObject::GameObject(const char* texturePath, int x, int y)
{
	texture = TextureManager::LoadTexture(texturePath, Game::renderer);
	gridPosition = Vec2i(x, y);
}

GameObject::GameObject(const char* texturePath, Vec2i _gridPosition) {
	texture = TextureManager::LoadTexture(texturePath, Game::renderer);
	gridPosition = _gridPosition;
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