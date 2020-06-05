#include "Enemy.h"

#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleBlocks.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "Score.h"

#include <iostream>

Enemy::Enemy(int x, int y, int color) : position(x, y)
{
	gridPosition.x = x;
	gridPosition.y = y;

	targetTile.x = x;
	targetTile.y = y;

	targetPosition.x = gridPosition.x * 16 + 8;
	targetPosition.y = gridPosition.y * 16 + 32;

	position.x = gridPosition.x * 16 + 8;
	position.y = gridPosition.y * 16 + 32;

	int xoffset = 0;
	int yoffset = 0;

	switch (color) {
	case 0:
		break;
	case 1:
		xoffset = 128;
		break;
	case 2:
		xoffset = 256;
		break;
	case 3:
		xoffset = 384;
		break;
	case 4:
		yoffset = 80;
		break;
	case 5:
		xoffset = 128;
		yoffset = 80;
		break;
	case 6:
		xoffset = 256;
		yoffset = 80;
		break;
	case 7:
		xoffset = 384;
		yoffset = 80;
		break;
	default:
		break;
	}

	spawnAnim.GenerateAnimation({ 0 + xoffset,128 + yoffset,96,16 }, 1, 6);
	spawnAnim.speed = 0.04f;
	spawnAnim.loop = false;

	currentAnim = &spawnAnim;
	spawning = true;

	idleAnim.GenerateAnimation({ 0 + xoffset,144 + yoffset,32,16 }, 1, 2);
	idleAnim.speed = 0.05f;
	idleAnim.loop = true;

	walkDownAnim.GenerateAnimation({ 0 + xoffset, 144 + yoffset, 32, 16 }, 1, 2);
	walkDownAnim.speed = 0.05f;
	walkDownAnim.loop = true;

	walkUpAnim.GenerateAnimation({ 64 + xoffset, 144 + yoffset, 32, 16 }, 1, 2);
	walkUpAnim.speed = 0.05f;
	walkUpAnim.loop = true;

	walkLeftAnim.GenerateAnimation({ 32 + xoffset, 144 + yoffset, 32, 16 }, 1, 2);
	walkLeftAnim.speed = 0.05f;
	walkLeftAnim.loop = true;

	walkRightAnim.GenerateAnimation({ 96 + xoffset, 144 + yoffset, 32, 16 }, 1, 2);
	walkRightAnim.speed = 0.05f;
	walkRightAnim.loop = true;

	breakDownAnim.GenerateAnimation({ 0 + xoffset, 160 + yoffset, 32, 16 }, 1, 2);
	breakDownAnim.speed = 0.13f;
	breakDownAnim.loop = true;

	breakUpAnim.GenerateAnimation({ 64 + xoffset, 160 + yoffset, 32, 16 }, 1, 2);
	breakUpAnim.speed = 0.13f;
	breakUpAnim.loop = true;

	breakLeftAnim.GenerateAnimation({ 32 + xoffset, 160 + yoffset, 32, 16 }, 1, 2);
	breakLeftAnim.speed = 0.13f;
	breakLeftAnim.loop = true;

	breakRightAnim.GenerateAnimation({ 96 + xoffset, 160 + yoffset, 32, 16 }, 1, 2);
	breakRightAnim.speed = 0.13f;
	breakRightAnim.loop = true;

	crushUp.GenerateAnimation({ 0 + xoffset,192 + yoffset,32,16 }, 1, 2);
	crushUp.speed = 0.2f;
	crushUp.loop = false;

	crushRight.GenerateAnimation({ 32 + xoffset,192 + yoffset,32,16 }, 1, 2);
	crushRight.speed = 0.2f;
	crushRight.loop = false;

	crushDown.GenerateAnimation({ 64 + xoffset,192 + yoffset,32,16 }, 1, 2);
	crushDown.speed = 0.2f;
	crushDown.loop = false;

	crushLeft.GenerateAnimation({ 96 + xoffset,192 + yoffset,32,16 }, 1, 2);
	crushLeft.speed = 0.2f;
	crushLeft.loop = false;

	stunAnim.GenerateAnimation({ 96 + xoffset,128 + yoffset,32,16 }, 1, 2);
	stunAnim.speed = 0.1f;
	stunAnim.loop = true;

	endStunAnim.GenerateAnimation({ 96 + xoffset,128 + yoffset,32,16 }, 1, 2);
	endStunAnim.GenerateAnimation({ 608, 208, 32, 16 }, 1, 2);
	endStunAnim.speed = 0.1f;
	endStunAnim.loop = true;

	GetNextTargetTile();
}

Enemy::~Enemy()
{
}

void Enemy::SetPosition(int x, int y) {
	gridPosition.x = x;
	gridPosition.y = y;

	targetTile.x = x;
	targetTile.y = y;

	targetPosition.x = gridPosition.x * 16 + 8;
	targetPosition.y = gridPosition.y * 16 + 32;

	position.x = gridPosition.x * 16 + 8;
	position.y = gridPosition.y * 16 + 32;
}

void Enemy::Update()
{

	if (stunned) {
		stunTimer += 1.0f / 60.0f;
		if (stunTimer > 1.5f) {
			currentAnim = &endStunAnim;
		}
		if (stunTimer > 3.0f) {
			//stunned = false;
		}
	}

	if ((spawning || stunned) && App->player->position.DistanceTo(position) < 10)
	{
		App->blocks->HatchNextEgg();
		destroy();
		App->score->AddScore(100);
	}

	if (currentAnim == &spawnAnim && currentAnim->HasFinished())
	{
		spawning = false;
		currentAnim = &idleAnim;
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
				crushed = true;
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
				crushed = true;
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
				crushed = true;
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
				crushed = true;
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

	if (currentAnim != &spawnAnim && !stunned && !crushed) {
		if (position.x < targetPosition.x) {
			if (!breakingBlock) currentAnim = &walkRightAnim;
			xpositionfraction += (pushed ? pushedSpeed : speed);
			position.x += xpositionfraction;
			xpositionfraction = std::fmod(xpositionfraction, 1.0f);
		}
		else if (position.x > targetPosition.x) {
			if (!breakingBlock) currentAnim = &walkLeftAnim;
			xpositionfraction -= (pushed ? pushedSpeed : speed);
			position.x += xpositionfraction - std::fmod(xpositionfraction, 1.0f);
			xpositionfraction = std::fmod(xpositionfraction, 1.0f);
		}

		if (position.y < targetPosition.y) {
			if (!breakingBlock) currentAnim = &walkDownAnim;
			ypositionfraction += (pushed ? pushedSpeed : speed);
			position.y += ypositionfraction;
			ypositionfraction = std::fmod(ypositionfraction, 1.0f);
		}
		else if (position.y > targetPosition.y) {
			if (!breakingBlock) currentAnim = &walkUpAnim;
			ypositionfraction -= (pushed ? pushedSpeed : speed);
			position.y += ypositionfraction - std::fmod(ypositionfraction, 1.0f);
			ypositionfraction = std::fmod(ypositionfraction, 1.0f);
		}
	}

	if ((currentAnim == &crushUp || currentAnim == &crushDown || currentAnim == &crushLeft || currentAnim == &crushRight) && currentAnim->HasFinished())
	{
		App->blocks->HatchNextEgg();
		destroy();
	}

	if ((currentAnim == &breakDownAnim || currentAnim == &breakUpAnim || currentAnim == &breakLeftAnim || currentAnim == &breakRightAnim) && currentAnim->loopCount > 1)
	{
		breakingBlock = false;
	}

	if (gridPosition == targetTile && !pushed && !suicide && !breakingBlock) {
		GetNextTargetTile();
	}

	if (suicide) {
		if (!suicideToWall && !suicideToCorner) {
			int dstLeft, dstRight, dstUp, dstDown;

			dstLeft = gridPosition.x;
			int closest = dstLeft;
			dstRight = 12 - gridPosition.x;
			closest = (closest < dstRight ? closest : dstRight);
			dstUp = gridPosition.y;
			closest = (closest < dstUp ? closest : dstUp);
			dstDown = 14 - gridPosition.y;
			closest = (closest < dstDown ? closest : dstDown);

			if (closest == dstLeft) {
				targetTile.x = 0;
				targetTile.y = gridPosition.y;
			}
			else if (closest == dstRight) {
				targetTile.x = 12;
				targetTile.y = gridPosition.y;
			}
			else if (closest == dstUp) {
				targetTile.x = gridPosition.x;
				targetTile.y = 0;
			}
			else if (closest == dstDown) {
				targetTile.x = gridPosition.x;
				targetTile.y = 14;
			}

			suicideToWall = true;
		}
		else if (suicideToWall && !suicideToCorner) {
			if (gridPosition.x == 0) {
				suicideToWall = false;
				suicideToCorner = true;
				targetTile.y = 0;
			}
			if (gridPosition.x == 12) {
				suicideToWall = false;
				suicideToCorner = true;
				targetTile.y = 14;
			}
			if (gridPosition.y == 0) {
				suicideToWall = false;
				suicideToCorner = true;
				targetTile.x = 0;
			}
			if (gridPosition.y == 14) {
				suicideToWall = false;
				suicideToCorner = true;
				targetTile.x = 12;
			}
		}

		if (suicideToCorner && gridPosition == targetTile && position == targetPosition) {
			destroy();
		}

	}

	if (position == targetPosition && currentAnim != &spawnAnim && !pushed) {
		moving = false;
		GetNextStepToTarget();
	}
	else {
		moving = true;
	}
}

void Enemy::GetNextTargetTile() {

	iPoint playerPos = App->player->gridPosition;

	std::normal_distribution<double> x_distribution(playerPos.x, 3.0);
	std::normal_distribution<double> y_distribution(playerPos.y, 3.0);

	int x;
	do {
		x = x_distribution(generator);
	} while (x > 12 || x < 0);

	int y;
	do {
		y = y_distribution(generator);
	} while (y > 14 || y < 0);

	targetTile = iPoint(x, y);
}

void Enemy::GetNextStepToTarget() {

	//float xdiff = ABS(App->player->gridPosition.x - gridPosition.x);
	//float ydiff = ABS(App->player->gridPosition.y - gridPosition.y);
	float xdiff = ABS(targetTile.x - gridPosition.x);
	float ydiff = ABS(targetTile.y - gridPosition.y);
	float totaldiff = xdiff + ydiff;

	if (totaldiff == 0) return;

	float prob = xdiff / totaldiff;

	std::uniform_real_distribution<double> distribution(0.0, 1.0);

	float sample = distribution(generator);

	bool canmovex = true;
	bool canmovey = true;
	bool blockx = false;
	bool blocky = false;

	if (gridPosition.x < targetTile.x) {
		if (App->blocks->BlockInGridPosition(gridPosition.x + 1, gridPosition.y)) {
			blockx = true;
		}
		if (blockx && !App->blocks->DestructibleByEnemy(gridPosition.x + 1, gridPosition.y)) {
			canmovex = false;
		}
	}
	else if (gridPosition.x > targetTile.x) {
		if (App->blocks->BlockInGridPosition(gridPosition.x - 1, gridPosition.y)) {
			blockx = true;
		}
		if (blockx && !App->blocks->DestructibleByEnemy(gridPosition.x - 1, gridPosition.y)) {
			canmovex = false;
		}
	}

	if (gridPosition.y < targetTile.y) {
		if (App->blocks->BlockInGridPosition(gridPosition.x, gridPosition.y + 1)) {
			blocky = true;
		}
		if (blocky && !App->blocks->DestructibleByEnemy(gridPosition.x, gridPosition.y + 1)) {
			canmovey = false;
		}
	}
	else if (gridPosition.y > targetTile.y) {
		if (App->blocks->BlockInGridPosition(gridPosition.x, gridPosition.y - 1)) {
			blocky = true;
		}
		if (blocky && !App->blocks->DestructibleByEnemy(gridPosition.x, gridPosition.y - 1)) {
			canmovey = false;
		}
	}

	if (suicide) {
		canmovex = true;
		canmovey = true;
	}

	if (!canmovex || !canmovey) {
		if (!canmovex && !canmovey && !suicide) {
			GetNextTargetTile();
			return;
		}
		if (!canmovex) {
			prob = 0;
		}
		if (!canmovey) {
			prob = 1;
		}
	}

	if (blockx) sample += 0.7f;
	if (blocky) sample -= 0.7f;

	if (sample < prob) {
		if (gridPosition.x < targetTile.x) {
			if (blockx) {
				App->blocks->BreakBlock(gridPosition.x + 1, gridPosition.y);
				breakingBlock = true;
				currentAnim = &breakRightAnim;
				currentAnim->Reset();
			}
			gridPosition.x++;
		}
		else if (gridPosition.x > targetTile.x) {
			if (blockx) {
				App->blocks->BreakBlock(gridPosition.x - 1, gridPosition.y);
				breakingBlock = true;
				currentAnim = &breakLeftAnim;
				currentAnim->Reset();
			}
			gridPosition.x--;
		}
		else {
			if (!suicide) GetNextTargetTile();
			return;
		}
	}
	else {
		if (gridPosition.y < targetTile.y) {
			if (blocky) {
				App->blocks->BreakBlock(gridPosition.x, gridPosition.y + 1);
				breakingBlock = true;
				currentAnim = &breakDownAnim;
				currentAnim->Reset();
			}
			gridPosition.y++;
		}
		else if (gridPosition.y > targetTile.y) {
			if (blocky) {
				App->blocks->BreakBlock(gridPosition.x, gridPosition.y - 1);
				breakingBlock = true;
				currentAnim = &breakUpAnim;
				currentAnim->Reset();
			}
			gridPosition.y--;
		}
		else {
			if (!suicide) GetNextTargetTile();
			return;
		}
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
	} else if (fromx > gridPosition.x) {
		direction = Directions::CrushLeft;
	} else if (fromy < gridPosition.y) {
		direction = Directions::CrushDown;
	} else if (fromy > gridPosition.y) {
		direction = Directions::CrushUp;
	}

	int x = 0;
	int y = 0;

	gridToPosition(gridPosition.x, gridPosition.y, x, y);

	position.x = x;
	position.y = y;

	targetPosition.x = x;
	targetPosition.y = y;

	moving = false;
	pushed = true;
	stunned = false;
}

void Enemy::WallStunned(int wallID)
{
	switch (wallID) {

	case 0:
		if (gridPosition.y == 0)
		{
			stunned = true;
			currentAnim = &stunAnim;
			currentAnim->Reset();

		}
		break;
	case 1:
		if (gridPosition.y == 14)
		{
			stunned = true;
			currentAnim = &stunAnim;
			currentAnim->Reset();
		}
		break;
	case 2:
		if (gridPosition.x == 0)
		{
			stunned = true;
			currentAnim = &stunAnim;
			currentAnim->Reset();
		}
		break;
	case 3:
		if (gridPosition.x == 12)
		{
			stunned = true;
			currentAnim = &stunAnim;
			currentAnim->Reset();
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
	App->enemies->enemyHasDied = true;
	SetToDelete();
}

void Enemy::positionToGrid(int gx, int gy, int& x, int& y) {
	x = (gx - 8) / 16;
	y = (gy - 32) / 16;
}

void Enemy::gridToPosition(int px, int py, int& x, int& y) {
	x = px * 16 + 8;
	y = py * 16 + 32;
}