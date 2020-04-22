#ifndef __WALL_H__
#define __WALL_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class Wall
{
public:
	// Constructor
	// Saves the spawn position for later movement calculations
	Wall(int x, int y);

	// Destructor
	virtual ~Wall();

	// Called from inhering enemies' Udpate
	// Updates animation and collider position
	virtual void Update();

	// Called from ModuleEnemies' Update
	virtual void Draw();

	void Shake();

public:
	// The current position in the world
	iPoint position;

	// The Wall's texture
	SDL_Texture* texture = nullptr;

protected:
	// A ptr to the current animation
	Animation* currentAnim = nullptr;
	Animation normalAnim;
	Animation shakeAnim;

private:
	int shakeCounter = 0;
	int shakeTime = 40;
};

#endif // __Wall_H__