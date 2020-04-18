#pragma once

#include "GameObject.h"

enum class PengoAnimations {
	WalkUp,
	WalkDown,
	WalkLeft,
	WalkRight,
	Die,
	PushUp,
	PushDown,
	PushLeft,
	PushRight
};

class Pengo : public GameObject {
public:
	Pengo();
	Pengo(Vec2i _position);
	~Pengo();

	void update() override;

protected:
	StateMachine<PengoAnimations, Animation*>* animator = nullptr;
	bool pushing = false;


private:
	void construct();
};