#pragma once

#include "GameObject.h"

enum class MenuBackgroundAnimations {
	Normal
};

class MenuBackground : public GameObject
{
public:
	MenuBackground();
	MenuBackground(Vec2i _position);
	~MenuBackground();

	void update();
	void construct();

private:
	StateMachine<MenuBackgroundAnimations, Animation*>* animator = nullptr;
};