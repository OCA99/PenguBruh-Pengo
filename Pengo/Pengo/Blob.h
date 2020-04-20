#pragma once

#include "GameObject.h"


enum class BlobAnimations {
	WalkUp,
	WalkDown,
	WalkLeft,
	WalkRight,
	Empty,
	Spawn
};

class Blob : public GameObject {
public:
	Blob();
	Blob(Vec2i _position);
	~Blob();

	void update();
	void pushed(GameObject* origin) override;
	void destroy();
	void move();

	enum class Directions {
		Up,
		Down,
		Left,
		Right,
		Stopped
	};
protected:
	StateMachine<BlobAnimations, Animation*>* animator = nullptr;

private:
	void construct();
	Directions direction = Directions::Stopped;
};