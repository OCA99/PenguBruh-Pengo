#pragma once

#include "Animation.h"
#include "p2Point.h"

struct Collider;

struct Star
{
public:
	// Constructor
	Star(int startPos);

	// Copy constructor
	Star(const Star& p);

	// Destructor
	~Star();

	// Called in ModuleStars' Update
	// Handles the logic of the Star
	// Returns false when the Star reaches its lifetime
	bool Update();

	// Sets flag for deletion and for the collider aswell
	void SetToDelete();

public:
	// Defines the position in the screen
	iPoint position;

	// A set of rectangle sprites
	Animation anim;

	// A flag for the Star removal. Important! We do not delete objects instantly
	bool pendingToDelete = false;
};