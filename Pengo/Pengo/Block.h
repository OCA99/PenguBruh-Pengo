#pragma once

#include "GameObject.h"

enum class BlockAnimations {
	Normal,
	Breaking,
	Empty
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
	void clean();

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
	virtual void construct() = 0;
	Directions direction = Directions::Stopped;
};