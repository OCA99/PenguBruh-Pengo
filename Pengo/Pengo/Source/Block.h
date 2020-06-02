#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class Block
{
public:
	// Constructor
	// Saves the spawn position for later movement calculations
	Block(int x, int y);

	// Destructor
	virtual ~Block();

	// Called from inhering enemies' Udpate
	// Updates animation and collider position
	virtual void Update();

	// Called from ModuleEnemies' Update
	virtual void Draw();

	// Sets flag for deletion and for the collider aswell
	virtual void SetToDelete();

	virtual void destroy();

	bool isMoving() { return moving; };

public:
	// The current position in the world
	iPoint position;
	iPoint targetPosition;
	iPoint gridPosition;

	// The Block's texture
	SDL_Texture* texture = nullptr;

	// A flag for the Block removal. Important! We do not delete objects instantly
	bool pendingToDelete = false;

	enum class Directions {
		Up,
		Down,
		Left,
		Right,
		Stopped
	};

	enum class Block_Type {
		NO_TYPE,
		NORMAL,
		DIAMOND,
		EGG
	};

	Directions direction = Directions::Stopped;

	virtual void Pushed(int fromx, int fromy);
	Block_Type type = Block_Type::NO_TYPE;

protected:
	// A ptr to the current animation
	Animation* currentAnim = nullptr;

private:
	int speed = 2;
	bool moving = false;
	int pushedEnemies = 0;

	void AddScore(int& pushedEnemies);
};

#endif // __Block_H__