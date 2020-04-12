#pragma once
//#include "Vec2.h"
//#include "SDL_image.h"
#include "Game.h"
class GameObject
{
	Vec2f position;
	Vec2i gridPosition;

	SDL_Texture* texture;

public:
	GameObject();
	GameObject(const char* texturePath, int _x, int _y);
	GameObject(const char* texturePath, Vec2i _gridPosition);
	~GameObject();

	void init();
	void update();
	void render();

	void clean();

};