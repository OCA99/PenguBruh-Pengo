#pragma once

#include <vector>
#include "Pengo.h"


class Player : public Pengo {
public:
	Player();
	Player(Vec2i _position);
	~Player();

	void update() override;
	void die();
	void push();
	bool checkForEnemy();

	enum class Directions {
		Up,
		Down,
		Left,
		Right
	};

private:
	void construct();

	std::vector<SDL_Keycode>* pressedKeys = nullptr;
	Directions direction;

};