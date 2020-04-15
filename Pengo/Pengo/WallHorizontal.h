#pragma once

#include "GameObject.h"

enum class WallHorizontalAnimations {
	Normal,
	Shake
};

class WallHorizontal : public GameObject {
public:
	WallHorizontal();
	WallHorizontal(Vec2i _position);
	~WallHorizontal();

	void update() override;
	void destroy();

protected:
	StateMachine<WallHorizontalAnimations, Animation*>* animator = nullptr;

private:
	void construct();
};