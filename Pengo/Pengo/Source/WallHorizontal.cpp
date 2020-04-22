#include "WallHorizontal.h"

#include "Application.h"

WallHorizontal::WallHorizontal(int x, int y) : Wall(x, y)
{
	normalAnim.GenerateAnimation({ 236,260,208,8 }, 1, 1);
	currentAnim = &normalAnim;

	shakeAnim.GenerateAnimation({ 456,260,224,16 }, 2, 1);
	shakeAnim.speed = 0.1f;
	shakeAnim.loop = true;
}

void WallHorizontal::Update()
{
	Wall::Update();
}