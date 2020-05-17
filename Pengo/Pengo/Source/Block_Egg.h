#ifndef BLOCK_EGG_H
#define BLOCK_EGG_H

#include "Block.h"

class Block_Egg : public Block
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Block_Egg(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void Pushed(int fromx, int fromy) override;

	void destroy() override;

	void NextBlobSpawn();

private:

	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation normalAnim;
	Animation destroyAnim;
};

#endif // Block_Egg_H