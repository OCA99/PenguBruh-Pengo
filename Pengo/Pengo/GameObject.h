#pragma once
#include "Game.h"
#include "Vec2.h"

class GameObject
{
	Vec2f position;
	Vec2i gridPosition;

	SDL_Texture* texture;

public:
	GameObject(const char* texturePath, int _x, int _y);
	GameObject(const char* texturePath, Vec2i _gridPosition);
	~GameObject();

	void update();
	void render();

};