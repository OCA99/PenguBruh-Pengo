#include "Block_Egg.h"

#include "Application.h"
#include "ModuleBlocks.h"
#include "ModuleEnemies.h"

Block_Egg::Block_Egg(int x, int y, int color) : Block(x, y)
{
	normalAnim.GenerateAnimation({ 708,0,16,16 }, 1, 1);

	initAnim.PushBack({ 708, 0, 16, 16 });
	initAnim.PushBack({ 724 + color * 16, 0, 16, 16 });
	initAnim.speed = 0.05f;
	initAnim.loop = true;

	/*destroyAnim.GenerateAnimation({ 708,48,144,16 }, 1, 9);
	destroyAnim.speed = 0.5f;
	destroyAnim.loop = false;*/

	currentAnim = &initAnim;

	type = Block_Type::EGG;
}

void Block_Egg::Update()
{
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	if (currentAnim == &initAnim) pause++;
	if (pause == 120)
	{
		pause = 0;
		currentAnim = &normalAnim;
	}
	if (currentAnim == &destroyAnim && currentAnim->HasFinished()) Block::destroy();

	if (hatching) {
		hatchTimer += 1.0f / 60.0f;
		if (hatchTimer > hatchDelay) {
			hatching = false;
			hatched = true;
			destroy();
			App->enemies->AddEnemy(gridPosition.x, gridPosition.y);
			App->blocks->remainingEggs--;
		}
	}

	if (currentAnim != &destroyAnim) {
		if (App->blocks->rainbow) currentAnim = &rainbowAnim;
		else currentAnim = &normalAnim;
	}

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
			App->blocks->waitToHatch++;
			App->enemies->AddEnemy(gridPosition.x, gridPosition.y);
			destroy();
		}
		break;
	case Directions::Left:
		x = gridPosition.x - 1;
		y = gridPosition.y;
		if (App->blocks->BlockInGridPosition(x, y) || !App->blocks->PositionInMap(x, y)) {
			App->blocks->waitToHatch++;
			App->enemies->AddEnemy(gridPosition.x, gridPosition.y);
			destroy();
		}
		break;
	case Directions::Right:
		x = gridPosition.x + 1;
		y = gridPosition.y;
		if (App->blocks->BlockInGridPosition(x, y) || !App->blocks->PositionInMap(x, y)) {
			App->blocks->waitToHatch++;
			App->enemies->AddEnemy(gridPosition.x, gridPosition.y);
			destroy();
		}
		break;
	case Directions::Down:
		x = gridPosition.x;
		y = gridPosition.y + 1;
		if (App->blocks->BlockInGridPosition(x, y) || !App->blocks->PositionInMap(x, y)) {
			App->blocks->waitToHatch++;
			App->enemies->AddEnemy(gridPosition.x, gridPosition.y);
			destroy();
		}
		break;
	default:
		break;
	}
}

void Block_Egg::NextBlobSpawn()
{
	hatching = true;
}
