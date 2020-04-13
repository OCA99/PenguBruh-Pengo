#pragma once

#include <iostream>
#include "Vec2.h"
#include "Animation.h"
#include "Game.h"
#include "TextureManager.h"
#include "StateMachine.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	void init();
	virtual void update();
	void render();
	void clean();

	Vec2f position;
	Vec2i gridPosition;

	Animation* animation = nullptr;
};