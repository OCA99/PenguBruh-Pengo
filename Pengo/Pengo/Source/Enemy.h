#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class Enemy
{
public:
	// Constructor
	// Saves the spawn position for later movement calculations
	Enemy(int x, int y);

	// Destructor
	virtual ~Enemy();

	// Called from inhering enemies' Udpate
	// Updates animation and collider position
	virtual void Update();

	// Called from ModuleEnemies' Update
	virtual void Draw();

	// Sets flag for deletion and for the collider aswell
	virtual void SetToDelete();

	void Pushed(int fromx, int fromy);

	void WallStunned(int wallID);

	void SetPosition(int x, int y);

	enum class Directions {
		Up,
		CrushUp,
		Down,
		CrushDown,
		Left,
		CrushLeft,
		Right,
		CrushRight,
		Stopped,

	};

	Directions direction = Directions::Stopped;

public:
	// The current position in the world
	iPoint position;
	iPoint gridPosition;
	iPoint targetPosition;

	// The enemy's texture
	SDL_Texture* texture = nullptr;

	// A flag for the enemy removal. Important! We do not delete objects instantly
	bool pendingToDelete = false;

	void destroy();

	bool stunned = false;

protected:
	// A ptr to the current animation
	Animation* currentAnim = nullptr;
	Animation spawnAnim;
	Animation walkDownAnim;
	Animation idleAnim;
	Animation crushUp;
	Animation crushDown;
	Animation crushLeft;
	Animation crushRight;
	Animation stunAnim;

private:
	int speed = 2;
	bool moving = false;
};

#endif // __ENEMY_H__