#pragma once

#include "GameObject.h"

enum class WallVerticalAnimations {
	Normal,
	Shake
};

class WallVertical : public GameObject {
public:
	WallVertical();
	WallVertical(Vec2i _position);
	~WallVertical();

	void update() override;
	void destroy();

protected:
	StateMachine<WallVerticalAnimations, Animation*>* animator = nullptr;

private:
	void construct();
};