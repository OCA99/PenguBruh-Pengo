#pragma once

#include "Wall.h"

class WallHorizontal : public Wall {
public:
	WallHorizontal();
	WallHorizontal(Vec2i _position);
	~WallHorizontal();

	void update() override;

protected:
	StateMachine<WallAnimations, Animation*>* animator = nullptr;

private:
	void construct() override;
};