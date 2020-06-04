#include "Block.h"

#include "Application.h"
//#include "ModuleCollisions.h"
//#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleBlocks.h"
#include "ModuleEnemies.h"

#include "Score.h"

#include <iostream>

Block::Block(int x, int y) : position(x, y)
{
	gridPosition.x = x;
	gridPosition.y = y;

	targetPosition.x = gridPosition.x * 16 + 8;
	targetPosition.y = gridPosition.y * 16 + 32;

	position.x = gridPosition.x * 16 + 8;
	position.y = gridPosition.y * 16 + 32;

	destroyAnim.GenerateAnimation({ 708,48,144,16 }, 1, 9);
	destroyAnim.speed = 0.5f;
	destroyAnim.loop = false;
}

Block::~Block()
{
	/*if (collider != nullptr)
		collider->pendingToDelete = true;*/
}

void Block::Update()
{
	if (currentAnim == &destroyAnim && currentAnim->HasFinished()) SetToDelete();
	if (!moving) {
		int x = 0;
		int y = 0;
		switch (direction) {
		case Directions::Up:
			x = gridPosition.x;
			y = gridPosition.y - 1;
			if (App->enemies->EnemyInGridPosition(x, y)) {
				pushedEnemies += App->enemies->PushEnemy(gridPosition.x, gridPosition.y, x, y);
			}
			if (App->blocks->BlockInGridPosition(x, y)) {
				direction = Directions::Stopped;
				App->audio->PlayFx(2, 0);
				AddScore(pushedEnemies);
			}
			else {
				gridPosition.y -= 1;
			}
			break;
		case Directions::Down:
			x = gridPosition.x;
			y = gridPosition.y + 1;
			if (App->enemies->EnemyInGridPosition(x, y)) {
				pushedEnemies += App->enemies->PushEnemy(gridPosition.x, gridPosition.y, x, y);
			}
			if (App->blocks->BlockInGridPosition(x, y)) {
				direction = Directions::Stopped;
				App->audio->PlayFx(2, 0);
				AddScore(pushedEnemies);
			}
			else {
				gridPosition.y += 1;
			}
			break;
		case Directions::Left:
			x = gridPosition.x - 1;
			y = gridPosition.y;
			if (App->enemies->EnemyInGridPosition(x, y)) {
				pushedEnemies += App->enemies->PushEnemy(gridPosition.x, gridPosition.y, x, y);
			}
			if (App->blocks->BlockInGridPosition(x, y)) {
				direction = Directions::Stopped;
				App->audio->PlayFx(2, 0);
				AddScore(pushedEnemies);
			}
			else {
				gridPosition.x -= 1;
			}
			break;
		case Directions::Right:
			x = gridPosition.x + 1;
			y = gridPosition.y;
			if (App->enemies->EnemyInGridPosition(x, y)) {
				pushedEnemies += App->enemies->PushEnemy(gridPosition.x, gridPosition.y, x, y);
			}
			if (App->blocks->BlockInGridPosition(x, y)) {
				direction = Directions::Stopped;
				App->audio->PlayFx(2, 0);
				AddScore(pushedEnemies);
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
}

void Block::Draw()
{
	if (currentAnim != nullptr)
	{
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
	}
}

void Block::SetToDelete()
{
	pendingToDelete = true;
	
	App->audio->PlayFx(6, 0);
	
	/*if (collider != nullptr)
		collider->pendingToDelete = true;*/
}

void Block::Pushed(int fromx, int fromy) {
	if (fromx < gridPosition.x) {
		App->audio->PlayFx(9, 0);
		direction = Directions::Right;
	}
	if (fromx > gridPosition.x) {
		App->audio->PlayFx(9, 0);
		direction = Directions::Left;
	}
	if (fromy < gridPosition.y) {
		App->audio->PlayFx(9, 0);
		direction = Directions::Down;
	}
	if (fromy > gridPosition.y) {
		App->audio->PlayFx(9, 0);
		direction = Directions::Up;
	}
}

void Block::destroy() {
	
	currentAnim = &destroyAnim;
}

void Block::AddScore(int& pushedEnemies) {
	switch (pushedEnemies) {
	case 1:
		App->score->AddScore(400);
		break;
	case 2:
		App->score->AddScore(1600);
		break;
	case 3:
		App->score->AddScore(3200);
		break;
	case 4:
		App->score->AddScore(6400);
		break;
	default:
		break;
	}
	pushedEnemies = 0;
}