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

	void update() override;
	void destroy();

protected:
	StateMachine<DiamondAnimations, Animation*>* animator = nullptr;

private:
	void construct();
};