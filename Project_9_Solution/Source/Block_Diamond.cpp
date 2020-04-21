#include "Block_Diamond.h"

#include "Application.h"

Block_Diamond::Block_Diamond(int x, int y) : Block(x, y)
{
	normalAnim.GenerateAnimation({ 708,16,16,16 }, 1, 1);
	currentAnim = &normalAnim;

	type = Block_Type::DIAMOND;
}

void Block_Diamond::Update()
{

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Block::Update();
}