#pragma once

#include "Block.h"

class Diamond : public Block {
public:
	Diamond();
	Diamond(Vec2i _position);
	~Diamond();

	void update();
	void clean();

private:
	void construct() override;
	Directions direction = Directions::Stopped;
};