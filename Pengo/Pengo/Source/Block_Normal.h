#ifndef BLOCK_NORMAL_H
#define BLOCK_NORMAL_H

#include "Block.h"

class Block_Normal : public Block
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Block_Normal(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void Pushed(int fromx, int fromy) override;

private:

	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation normalAnim;
};

#endif // Block_Normal_H