#pragma once

#include <iostream>
#include <algorithm>
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
	virtual void update();
	void render();
	void clean();
	void moveToGridPosition(Vec2i position);

	Vec2i position;

	Animation* animation = nullptr;
	Vec2i gridPosition;
	GridManager* gridManager;

	int type = 0;
	Vec2i targetPosition = Vec2i();
private:

	void stepToTargetPosition();
protected:
	bool moving = false;
	int speed = 0;
};