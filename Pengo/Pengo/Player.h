#pragma once

#include <vector>
#include "Pengo.h"

enum class Directions {
	Up,
	Down,
	Left,
	Right
};

class Player : public Pengo {
public:
	Player();
	Player(Vec2i _position);
	~Player();

	void update() override;

private:
	void construct();

	std::vector<SDL_Keycode>* pressedKeys = nullptr;
	Directions direction;
};