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

	void update() override;
	void destroy();

protected:
	StateMachine<BlockAnimations, Animation*>* animator = nullptr;

private:
	void construct();
};