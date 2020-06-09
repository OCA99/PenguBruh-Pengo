#ifndef BLOCK_DIAMOND_H
#define BLOCK_DIAMOND_H

#include "Block.h"

class Block_Diamond : public Block
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Block_Diamond(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void DiamondsTogether(int x, int y);

	int Dia = 1;
	void BlockTogether();

	bool oscaretmato;

private:

	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation normalAnim;
	Animation togetherAllAnim;
	Animation twogetherAnim;
};

#endif // Block_Normal_H