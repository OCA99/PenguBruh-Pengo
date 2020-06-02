#include "Enemy.h"

#include "Application.h"
//#include "ModuleCollisions.h"
//#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleBlocks.h"
#include "ModulePlayer.h"

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

	idleAnim.GenerateAnimation({ 0 + xoffset,144 + yoffset,32,16 }, 1, 2);
	idleAnim.speed = 0.05f;
	currentAnim = &idleAnim;

	crushUp.GenerateAnimation({ 0 + xoffset,192 + yoffset,32,16 }, 1, 2);
	crushUp.speed = 0.2f;
	crushUp.loop = false;

	crushRight.GenerateAnimation({ 32 + xoffset,192 + yoffset,32,16 }, 1, 2);
	crushRight.speed = 0.2f;
	crushRight.loop = false;

	crushDown.GenerateAnimation({ 48 + xoffset,192 + yoffset,32,16 }, 1, 2);
	crushDown.speed = 0.2f;
	crushDown.loop = false;

	crushLeft.GenerateAnimation({ 64 + xoffset,192 + yoffset,32,16 }, 1, 2);
	crushLeft.speed = 0.2f;
	crushLeft.loop = false;

	stunAnim.GenerateAnimation({ 96 + xoffset,128 + yoffset,32,16 }, 1, 2);
	stunAnim.speed = 0.05f;
	stunAnim.loop = true;

	GetNextTargetTile();
}

Enemy::~Enemy()
{
	/*if (collider != nullptr)
		collider->pendingToDelete = true;*/
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

	if (stunned && App->player->position == position)
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

	if (currentAnim != &spawnAnim && !stunned) {
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

	if (gridPosition == targetTile) {
		GetNextTargetTile();
	}

	if (position == targetPosition && currentAnim != &spawnAnim) {
		GetNextStepToTarget();
		moving = false;
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
	} while (y > 12 || y < 0);

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

	if (!canmovex || !canmovey) {
		if (!canmovex && !canmovey) {
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
			}
			gridPosition.x++;
		}
		else if (gridPosition.x > targetTile.x) {
			if (blockx) {
				App->blocks->BreakBlock(gridPosition.x - 1, gridPosition.y);
			}
			gridPosition.x--;
		}
		else {
			GetNextTargetTile();
			return;
		}
	}
	else {
		if (gridPosition.y < targetTile.y) {
			if (blocky) {
				App->blocks->BreakBlock(gridPosition.x, gridPosition.y + 1);
			}
			gridPosition.y++;
		}
		else if (gridPosition.y > targetTile.y) {
			if (blocky) {
				App->blocks->BreakBlock(gridPosition.x, gridPosition.y - 1);
			}
			gridPosition.y--;
		}
		else {
			GetNextTargetTile();
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