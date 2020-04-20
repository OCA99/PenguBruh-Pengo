#pragma once

#include "GameObject.h"

enum class CreditsAnimations {
	Normal
};

class Credits : public GameObject
{
public:
	Credits();
	Credits(Vec2i _position);
	~Credits();

	void update();
	void construct();

private:
	StateMachine<CreditsAnimations, Animation*>* animator = nullptr;
};