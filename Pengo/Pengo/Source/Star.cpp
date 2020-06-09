#include "Star.h"

#include "Collider.h"

Star::Star(int startPos)
{
	position.SetToZero();

	anim.GenerateAnimation({ 856, 256, 128, 8 }, 1, 16);
	anim.speed = 0.65f;

	anim.currentFrame = startPos;
}

Star::Star(const Star& p) : anim(p.anim), position(p.position)
{

}

Star::~Star()
{
}

#include <iostream>

bool Star::Update()
{

	anim.Update();

	return true;
}

void Star::SetToDelete()
{
	pendingToDelete = true;
}