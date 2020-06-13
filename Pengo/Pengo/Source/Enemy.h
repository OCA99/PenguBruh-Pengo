#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"

#include <random>
#include <stdlib.h> // used for random
#include <time.h> // used for random
#include <math.h>

struct SDL_Texture;
struct Collider;

class Enemy
{
public:
	// Constructor
	// Saves the spawn position for later movement calculations
	Enemy(int x, int y, int color);

	// Destructor
	virtual ~Enemy();

	// Called from inhering enemies' Udpate
	// Updates animation and collider position
	virtual void Update();

	// Called from ModuleEnemies' Update
	virtual void Draw();

	// Sets flag for deletion and for the collider aswell
	virtual void SetToDelete();

	void Pushed(int fromx, int fromy, int gridx, int gridy);

	void WallStunned(int wallID);

	void SetPosition(int x, int y);

	void GetNextTargetTile();

	void GetNextStepToTarget();

	int ABS(int x) { return (x > 0 ? x : -x); }

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

	void Suicide() { suicide = true; }
	void UnSuicide() {
		suicide = false;
		suicideToCorner = false;
		suicideToWall = false;
	}

	void Reset();

public:
	// The current position in the world
	iPoint position;
	iPoint gridPosition;
	iPoint targetPosition;
	iPoint targetTile;

	float xpositionfraction = 0;
	float ypositionfraction = 0;

	// The enemy's texture
	SDL_Texture* texture = nullptr;

	// A flag for the enemy removal. Important! We do not delete objects instantly
	bool pendingToDelete = false;

	void destroy();

	bool stunned = false;
	bool pushed = false;
	bool spawning = false;

	bool paused = false;

	void positionToGrid(int gx, int gy, int& x, int& y);
	void gridToPosition(int px, int py, int& x, int& y);

protected:
	// A ptr to the current animation
	Animation* currentAnim = nullptr;
	Animation spawnAnim;
	Animation idleAnim;
	Animation walkUpAnim;
	Animation walkDownAnim;
	Animation walkLeftAnim;
	Animation walkRightAnim;
	Animation crushUp;
	Animation crushDown;
	Animation crushLeft;
	Animation crushRight;
	Animation breakUpAnim;
	Animation breakDownAnim;
	Animation breakLeftAnim;
	Animation breakRightAnim;
	Animation stunAnim;
	Animation endStunAnim;

private:
	int pushedSpeed = 3;
	float speed = 0.8f;
	bool moving = false;
	bool crushed = false;
	bool breakingBlock = false;
	std::random_device generator;
	bool suicide = false;
	bool suicideToWall = false;
	bool suicideToCorner = false;

	float stunTimer = 0.0f;

	float ABS(float x) {
		return x > 0 ? x : -x;
	}
};

#endif // __ENEMY_H__