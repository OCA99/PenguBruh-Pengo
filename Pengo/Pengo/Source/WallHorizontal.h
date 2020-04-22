#ifndef WALL_HORIZONTAL_H
#define WALL_HORIZONTAL_H

#include "Wall.h"

class WallHorizontal : public Wall
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	WallHorizontal(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

private:

	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies

};

#endif // Block_Normal_H