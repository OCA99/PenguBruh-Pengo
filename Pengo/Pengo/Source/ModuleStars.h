#pragma once

#include "Module.h"

#include "Globals.h"
#include "Star.h"

#define MAX_ACTIVE_STARS 150

struct SDL_Texture;
struct Collider;

class ModuleStars : public Module
{
public:
	// Constructor
	// Initializes all the particles in the array to nullptr
	ModuleStars(bool startEnabled);

	//Destructor
	~ModuleStars();

	// Called when the module is activated
	// Loads the necessary textures for the particles
	bool Start() override;

	// Called at the beginning of the application loop
	// Removes all particles pending to delete
	Update_Status PreUpdate() override;

	// Called at the middle of the application loop
	// Iterates all the particles and calls its Update()
	// Removes any "dead" particles
	Update_Status Update() override;

	// Called at the end of the application loop
	// Iterates all the particles and draws them
	Update_Status PostUpdate() override;

	// Called on application exit
	// Destroys all active particles left in the array
	bool CleanUp() override;

	// Called when a particle collider hits another collider

	// Creates a new particle and adds it to the array
	// Param particle	- A template particle from which the new particle will be created
	// Param x, y		- Position x,y in the screen (upper left axis)
	// Param delay		- Delay time from the moment the function is called until the particle is displayed in screen
	void AddStar(int x, int y, int startPos);
	//Particle* AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType = Collider::Type::NONE, uint delay = 0);

	bool starsActive = false;

	
	void ActivateStars();

public:
	

private:
	// Particles spritesheet loaded into an SDL Texture
	SDL_Texture* texture = nullptr;

	// An array to store and handle all the particles
	Star* stars[MAX_ACTIVE_STARS] = { nullptr };

	float starsCounter = 0.0f;

};
