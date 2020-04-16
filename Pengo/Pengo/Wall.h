#pragma once

#include "GameObject.h"

enum class WallAnimations {
	Normal,
	Shake
};

class Wall : public GameObject {
public:
	Wall();
	Wall(Vec2i _position);
	~Wall();
	virtual void update() = 0;

protected:
	StateMachine<WallAnimations, Animation*>* animator = nullptr;

private:
	virtual void construct() = 0;
};
