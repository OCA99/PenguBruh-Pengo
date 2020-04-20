#pragma once

#include "Block.h"

class NormalBlock : public Block {
public:
	NormalBlock();
	NormalBlock(Vec2i _position);
	~NormalBlock();

	void update();
	void clean();

private:
	void construct() override;
	Directions direction = Directions::Stopped;
};