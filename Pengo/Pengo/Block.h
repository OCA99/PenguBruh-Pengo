#pragma once

#include "GameObject.h"

enum class BlockAnimations {
	Normal,
	Breaking
};

class Block : public GameObject {
public:
	Block();
	Block(Vec2i _position);
	~Block();

	void update();
	void destroy();
	void pushed(GameObject* origin) override;
	void move();

	enum class Directions {
		Up,
		Down,
		Left,
		Right,
		Stopped
	};

protected:
	StateMachine<BlockAnimations, Animation*>* animator = nullptr;

private:
	void construct();
	Directions direction = Directions::Stopped;
};