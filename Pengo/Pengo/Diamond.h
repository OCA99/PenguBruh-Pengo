#pragma once

#include "GameObject.h"

enum class DiamondAnimations {
	Normal
};

class Diamond : public GameObject {
public:
	Diamond();
	Diamond(Vec2i _position);
	~Diamond();

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
	StateMachine<DiamondAnimations, Animation*>* animator = nullptr;

private:
	void construct();
	Directions direction = Directions::Stopped;
};