#include "WallVertical.h"

#include "Application.h"

WallVertical::WallVertical(int x, int y) : Wall(x, y)
{
	normalAnim.GenerateAnimation({ 216,0,8,256 }, 1, 1);
	currentAnim = &normalAnim;

	shakeAnim.GenerateAnimation({ 684,0,16,256 }, 1, 2);
	shakeAnim.speed = 0.1f;
	shakeAnim.loop = true;
}

void WallVertical::Update()
{
	Wall::Update();
}