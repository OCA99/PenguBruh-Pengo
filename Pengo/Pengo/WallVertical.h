#pragma once

#include "Wall.h"

class WallVertical : public Wall {
public:
	WallVertical();
	WallVertical(Vec2i _position);
	~WallVertical();

	void update() override;

protected:
	StateMachine<WallAnimations, Animation*>* animator = nullptr;

private:
	void construct() override;
};