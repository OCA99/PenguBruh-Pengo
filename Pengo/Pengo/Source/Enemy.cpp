#include "Enemy.h"

#include "Application.h"
//#include "ModuleCollisions.h"
//#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleBlocks.h"
#include "ModulePlayer.h"

#include <stdio.h>

Enemy::Enemy(int x, int y) : position(x, y)
{
	gridPosition.x = x;
	gridPosition.y = y;

	targetPosition.x = gridPosition.x * 16 + 8;
	targetPosition.y = gridPosition.y * 16 + 32;

	position.x = gridPosition.x * 16 + 8;
	position.y = gridPosition.y * 16 + 32;

	spawnAnim.GenerateAnimation({ 128,128,96,16 }, 1, 6);
	spawnAnim.speed = 0.04f;
	spawnAnim.loop = false;

	idleAnim.GenerateAnimation({ 128,144,32,16 }, 1, 2);
	idleAnim.speed = 0.05f;
	currentAnim = &idleAnim;

	crushUp.GenerateAnimation({ 128,192,32,16 }, 1, 2);
	crushUp.speed = 0.2f;
	crushUp.loop = false;

	crushRight.GenerateAnimation({ 160,192,32,16 }, 1, 2);
	crushRight.speed = 0.2f;
	crushRight.loop = false;

	crushDown.GenerateAnimation({ 176,192,32,16 }, 1, 2);
	crushDown.speed = 0.2f;
	crushDown.loop = false;

	crushLeft.GenerateAnimation({ 192,192,32,16 }, 1, 2);
	crushLeft.speed = 0.2f;
	crushLeft.loop = false;

	stunAnim.GenerateAnimation({ 224,128,32,16 }, 1, 2);
	stunAnim.speed = 0.05f;
	stunAnim.loop = true;

}

Enemy::~Enemy()
{
	/*if (collider != nullptr)
		collider->pendingToDelete = true;*/
}

void Enemy::SetPosition(int x, int y) {
	gridPosition.x = x;
	gridPosition.y = y;

	targetPosition.x = gridPosition.x * 16 + 8;
	targetPosition.y = gridPosition.y * 16 + 32;

	position.x = gridPosition.x * 16 + 8;
	position.y = gridPosition.y * 16 + 32;
}

void Enemy::Update()
{

	if (stunned && App->player->gridPosition == gridPosition)
	{
		destroy();
		//PTS = 100pts
	}

	if (!stunned)
	{
		currentAnim = &spawnAnim;

		if (currentAnim == &spawnAnim && currentAnim->HasFinished())
		{
			currentAnim = &idleAnim;
		}
	}


	if (!moving) {

		int x = 0;
		int y = 0;
		switch (direction) {
		case Directions::CrushUp:

			x = gridPosition.x;
			y = gridPosition.y - 1;
			if (App->blocks->BlockInGridPosition(x, y) || y == -1) {
				currentAnim = &crushUp;
				App->audio->PlayFx(13, 0);
			}
			else {
				gridPosition.y -= 1;
			}
			break;
		case Directions::CrushDown:

			x = gridPosition.x;
			y = gridPosition.y + 1;
			if (App->blocks->BlockInGridPosition(x, y) || y == 15) {
				currentAnim = &crushDown;
				App->audio->PlayFx(13, 0);
			}
			else {
				gridPosition.y += 1;
			}
			break;
		case Directions::CrushLeft:

			x = gridPosition.x - 1;
			y = gridPosition.y;
			if (App->blocks->BlockInGridPosition(x, y) || x == -1) {
				currentAnim = &crushLeft;
				App->audio->PlayFx(13, 0);
			}
			else {
				gridPosition.x -= 1;
			}
			break;
		case Directions::CrushRight:

			x = gridPosition.x + 1;
			y = gridPosition.y;
			if (App->blocks->BlockInGridPosition(x, y) || x == 13) {
				currentAnim = &crushRight;
				App->audio->PlayFx(13, 0);
			}
			else {
				gridPosition.x += 1;
			}
			break;
		default:
			break;
		}
	}

	if (currentAnim != nullptr)
		currentAnim->Update();

	if (gridPosition.x < 0) {
		direction = Directions::Stopped;
		gridPosition.x = 0;
	}
	if (gridPosition.x > 12) {
		direction = Directions::Stopped;
		gridPosition.x = 12;
	}
	if (gridPosition.y < 0) {
		direction = Directions::Stopped;
		gridPosition.y = 0;
	}
	if (gridPosition.y > 14) {
		direction = Directions::Stopped;
		gridPosition.y = 14;
	}

	targetPosition.x = gridPosition.x * 16 + 8;
	targetPosition.y = gridPosition.y * 16 + 32;

	if (position.x < targetPosition.x) {
		position.x += speed;
	}
	else if (position.x > targetPosition.x) {
		position.x -= speed;
	}

	if (position.y < targetPosition.y) {
		position.y += speed;
	}
	else if (position.y > targetPosition.y) {
		position.y -= speed;
	}

	if (position.x == targetPosition.x && position.y == targetPosition.y) {
		moving = false;
	}
	else {
		moving = true;
	}

	if ((currentAnim == &crushUp || currentAnim == &crushDown || currentAnim == &crushLeft || currentAnim == &crushRight) && currentAnim->HasFinished())
	{
		App->blocks->HatchNextEgg();
		destroy();
		//Score Counter
		//1 enemie counts 400pts
		//2 enemies with one block = pts 1600
		//3 =3200pts
		//4 = 6400pts
	}
}

void Enemy::Draw()
{
	if (currentAnim != nullptr) {
		SDL_Rect r = currentAnim->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
	}
}

void Enemy::Pushed(int fromx, int fromy) {

	if (fromx < gridPosition.x) {
		direction = Directions::CrushRight;
	}
	if (fromx > gridPosition.x) {
		direction = Directions::CrushLeft;
	}
	if (fromy < gridPosition.y) {
		direction = Directions::CrushDown;
	}
	if (fromy > gridPosition.y) {
		direction = Directions::CrushUp;
	}

}

void Enemy::WallStunned(int wallID)
{
	switch (wallID) {

	case 0:
		for (int i = 0; i <= 12; i++)
		{
			if (gridPosition.x == i && gridPosition.y == 0)
			{
				stunned = true;
				currentAnim = &stunAnim;
			}
		}
		break;
	case 1:
		for (int i = 0; i <= 12; i++)
		{
			if (gridPosition.x == i && gridPosition.y == 14)
			{
				stunned = true;
				currentAnim = &stunAnim;
			}
		}
		break;
	case 2:
		for (int i = 0; i <= 14; i++)
		{
			if (gridPosition.y == i && gridPosition.x == 0)
			{
				stunned = true;
				currentAnim = &stunAnim;
			}
		}
		break;
	case 3:
		for (int i = 0; i <= 14; i++)
		{
			if (gridPosition.y == i && gridPosition.x == 12)
			{
				stunned = true;
				currentAnim = &stunAnim;
			}
		}
		break;
	default:
		break;

	}
}

void Enemy::SetToDelete()
{
	pendingToDelete = true;
	/*if (collider != nullptr)
		collider->pendingToDelete = true;*/
}

void Enemy::destroy() {
	//App->audio->PlayFx(10, 0);
	SetToDelete();
}