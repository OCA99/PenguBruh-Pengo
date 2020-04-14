#pragma once

#include "GameObject.h"

enum class PengoAnimations {
	WalkUp,
	WalkDown,
	WalkLeft,
	WalkRight
};

class Pengo : public GameObject {
public:
	Pengo();
	Pengo(Vec2i _position);
	~Pengo();

	void update() override;

protected:
	StateMachine<PengoAnimations, Animation*>* animator = nullptr;

private:
	void construct();
};