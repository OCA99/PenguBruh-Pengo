#include "Block_Egg.h"

#include "Application.h"
#include "ModuleBlocks.h"
#include "ModuleEnemies.h"

Block_Egg::Block_Egg(int x, int y) : Block(x, y)
{
	normalAnim.GenerateAnimation({ 708,0,16,16 }, 1, 1);
	currentAnim = &normalAnim;

	destroyAnim.GenerateAnimation({ 708,48,144,16 }, 1, 9);
	destroyAnim.speed = 0.5f;
	destroyAnim.loop = false;

	type = Block_Type::EGG;
}

void Block_Egg::Update()
{
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	if (currentAnim == &destroyAnim && currentAnim->HasFinished()) Block::destroy();
	Block::Update();
}

void Block_Egg::Pushed(int fromx, int fromy) {
	Block::Pushed(fromx, fromy);
	int x = 0;
	int y = 0;
	switch (direction) {
	case Directions::Up:
		x = gridPosition.x;
		y = gridPosition.y - 1;
		if (App->blocks->BlockInGridPosition(x, y) || !App->blocks->PositionInMap(x, y)) {
			NextBlobSpawn();
		}
		break;
	case Directions::Left:
		x = gridPosition.x - 1;
		y = gridPosition.y;
		if (App->blocks->BlockInGridPosition(x, y) || !App->blocks->PositionInMap(x, y)) {
			NextBlobSpawn();
		}
		break;
	case Directions::Right:
		x = gridPosition.x + 1;
		y = gridPosition.y;
		if (App->blocks->BlockInGridPosition(x, y) || !App->blocks->PositionInMap(x, y)) {
			NextBlobSpawn();
		}
		break;
	case Directions::Down:
		x = gridPosition.x;
		y = gridPosition.y + 1;
		if (App->blocks->BlockInGridPosition(x, y) || !App->blocks->PositionInMap(x, y)) {
			NextBlobSpawn();
		}
		break;
	default:
		break;
	}
}

void Block_Egg::NextBlobSpawn()
{
	destroy();
	App->enemies->AddEnemy(gridPosition.x, gridPosition.y);
}

void Block_Egg::destroy() {
	currentAnim = &destroyAnim;
}
