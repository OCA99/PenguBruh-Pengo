#pragma once

#include <vector>
#include "GameObject.h"

enum class PengoAnimations {
	WalkUp,
	WalkDown,
	WalkLeft,
	WalkRight
};

enum class Directions {
	Up,
	Down,
	Left,
	Right
};

class Pengo : public GameObject {
public:
	Pengo();
	~Pengo();

	void update() override;

private:
	StateMachine<PengoAnimations, Animation*>* animator = nullptr;
	std::vector<SDL_Keycode>* pressedKeys = nullptr;
	Directions direction;
};