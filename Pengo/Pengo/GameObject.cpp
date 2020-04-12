#include "GameObject.h"
#include "TextureManager.h"
#include "Game.h"

GameObject::GameObject(const char* texturePath, int x, int y)
{
	texture = TextureManager::LoadTexture(texturePath, Game::renderer);
	gridPosition = Vec2i(x, y);
}

GameObject::GameObject(const char* texturePath, Vec2i _gridPosition) {
	texture = TextureManager::LoadTexture(texturePath, Game::renderer);
	gridPosition = _gridPosition;
}

void GameObject::update()
{

}

void GameObject::render()
{

}