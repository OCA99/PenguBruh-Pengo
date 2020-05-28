#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

#include <SDL\include\SDL_timer.h>

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer(bool startEnabled);
	
	// Destructor
	~ModulePlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	Update_Status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	Update_Status PostUpdate() override;

	void Reset();

	void SetPosition(int x, int y);


	enum class Directions {
		Up,
		Down,
		Left,
		Right
	};


public:
	// Position of the player in the map
	iPoint position;
	iPoint targetPosition;
	iPoint gridPosition;

	bool moving = false;

	bool dead = false;
	bool instaloss = false;
	// The speed in which we move the player (pixels per frame)
	int speed = 1;

	//Counter to repeat animations
	int deadPause = 0;

	int lifes = 2;
	

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;
	
	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation idleAnim;
	Animation walkUpAnim;
	Animation walkDownAnim;
	Animation walkLeftAnim;
	Animation walkRightAnim;
	Animation pushUpAnim;
	Animation pushDownAnim;
	Animation pushLeftAnim;
	Animation pushRightAnim;
	Animation dieAnim;


	// The player's collider
	//Collider* collider = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;

	int lastPressed = NULL;
	
	bool aPressed = true;

	// Sound effects indices
	//uint laserFx = 0;
	//uint explosionFx = 0;

	// Font score index
	//uint score = 000;
	//int scoreFont = -1;
	//char scoreText[10] = { "\0" };

private:
	Directions direction;
	void positionToGrid(int gx, int gy, int& x, int& y);
};

#endif //!__MODULE_PLAYER_H__