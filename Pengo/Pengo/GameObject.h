#pragma once

#include <iostream>
#include "Vec2.h"
#include "Animation.h"
#include "TextureManager.h"
#include "StateMachine.h"
#include "Game.h"

class GameObject
{
public:
	GameObject();
	GameObject(Vec2i _position);
	~GameObject();

	void init();
	virtual void update() = 0;
	void render();
	void clean();

	Vec2i position;

	Animation* animation = nullptr;
};