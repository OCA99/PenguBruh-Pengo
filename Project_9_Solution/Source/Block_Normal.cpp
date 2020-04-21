#include "Block_Normal.h"

#include "Application.h"
#include "ModuleBlocks.h"

Block_Normal::Block_Normal(int x, int y) : Block(x, y)
{
	normalAnim.GenerateAnimation({ 708,0,16,16 }, 1, 1);
	currentAnim = &normalAnim;

	destroyAnim.GenerateAnimation({ 708,48,144,16 }, 1, 9);
	destroyAnim.speed = 0.5f;
	destroyAnim.loop = false;

	type = Block_Type::NORMAL;
}

void Block_Normal::Update()
{

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	if (currentAnim == &destroyAnim && currentAnim->HasFinished()) Block::destroy();
	Block::Update();
}

void Block_Normal::Pushed(int fromx, int fromy) {
	Block::Pushed(fromx, fromy);
	int x = 0;
	int y = 0;
	switch (direction) {
	case Directions::Up:
		x = gridPosition.x;
		y = gridPosition.y - 1;
		if (App->blocks->BlockInGridPosition(x, y) || !App->blocks->PositionInMap(x, y)) {
			destroy();
		}
		break;
	case Directions::Left:
		x = gridPosition.x - 1;
		y = gridPosition.y;
		if (App->blocks->BlockInGridPosition(x, y) || !App->blocks->PositionInMap(x, y)) {
			destroy();
		}
		break;
	case Directions::Right:
		x = gridPosition.x + 1;
		y = gridPosition.y;
		if (App->blocks->BlockInGridPosition(x, y) || !App->blocks->PositionInMap(x, y)) {
			destroy();
		}
		break;
	case Directions::Down:
		x = gridPosition.x;
		y = gridPosition.y + 1;
		if (App->blocks->BlockInGridPosition(x, y) || !App->blocks->PositionInMap(x, y)) {
			destroy();
		}
		break;
	default:
		break;
	}
}

void Block_Normal::destroy() {
	currentAnim = &destroyAnim;
}