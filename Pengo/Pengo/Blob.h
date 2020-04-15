#pragma once

#include "GameObject.h"

enum class BlobAnimations {
	WalkUp,
	WalkDown,
	WalkLeft,
	WalkRight,
	Spawn
};

class Blob : public GameObject {
public:
	Blob();
	Blob(Vec2i _position);
	~Blob();

	void update() override;

protected:
	StateMachine<BlobAnimations, Animation*>* animator = nullptr;

private:
	void construct();
};