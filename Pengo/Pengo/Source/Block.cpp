#include "Block.h"

#include "Application.h"
//#include "ModuleCollisions.h"
//#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleBlocks.h"
#include "ModuleEnemies.h"

Block::Block(int x, int y) : position(x, y)
{
	gridPosition.x = x;
	gridPosition.y = y;

	targetPosition.x = gridPosition.x * 16 + 8;
	targetPosition.y = gridPosition.y * 16 + 32;

	position.x = gridPosition.x * 16 + 8;
	position.y = gridPosition.y * 16 + 32;
}

Block::~Block()
{
	/*if (collider != nullptr)
		collider->pendingToDelete = true;*/
}

void Block::Update()
{
	if (!moving) {
		int x = 0;
		int y = 0;
		switch (direction) {
		case Directions::Up:
			x = gridPosition.x;
			y = gridPosition.y - 1;
			if (App->enemies->EnemyInGridPosition(x, y)) App->enemies->PushEnemy(gridPosition.x, gridPosition.y, x, y);
			if (App->blocks->BlockInGridPosition(x, y)) {
				direction = Directions::Stopped;
			}
			else {
				gridPosition.y -= 1;
			}
			break;
		case Directions::Down:
			x = gridPosition.x;
			y = gridPosition.y + 1;
			if (App->enemies->EnemyInGridPosition(x, y)) App->enemies->PushEnemy(gridPosition.x, gridPosition.y, x, y);
			if (App->blocks->BlockInGridPosition(x, y)) {
				direction = Directions::Stopped;
			}
			else {
				gridPosition.y += 1;
			}
			break;
		case Directions::Left:
			x = gridPosition.x - 1;
			y = gridPosition.y;
			if (App->enemies->EnemyInGridPosition(x, y)) App->enemies->PushEnemy(gridPosition.x, gridPosition.y, x, y);
			if (App->blocks->BlockInGridPosition(x, y)) {
				direction = Directions::Stopped;
			}
			else {
				gridPosition.x -= 1;
			}
			break;
		case Directions::Right:
			x = gridPosition.x + 1;
			y = gridPosition.y;
			if (App->enemies->EnemyInGridPosition(x, y)) App->enemies->PushEnemy(gridPosition.x, gridPosition.y, x, y);
			if (App->blocks->BlockInGridPosition(x, y)) {
				direction = Directions::Stopped;
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
		direction = Directions::Right;
	}
	if (fromx > gridPosition.x) {
		direction = Directions::Left;
	}
	if (fromy < gridPosition.y) {
		direction = Directions::Down;
	}
	if (fromy > gridPosition.y) {
		direction = Directions::Up;
	}
}

void Block::destroy() {
	
	SetToDelete();
}