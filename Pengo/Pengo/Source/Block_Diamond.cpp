#include "Block_Diamond.h"
#include "ModuleBlocks.h"
#include "Score.h"
#include "Application.h"
#include <stdio.h>
Block_Diamond::Block_Diamond(int x, int y) : Block(x, y)
{
	normalAnim.GenerateAnimation({ 708,16,16,16 }, 1, 1);
	currentAnim = &normalAnim;

	togetherAllAnim.GenerateAnimation({ 708, 16,144,32 }, 2, 9);
	togetherAllAnim.speed = 0.085f;
	togetherAllAnim.loop = true;

	twogetherAnim.GenerateAnimation({ 708,32, 32,16 }, 1, 2);
	twogetherAnim.speed = 0.5f;
	twogetherAnim.loop = true;

	type = Block_Type::DIAMOND;
}

void Block_Diamond::Update()
{
	if (Dia == 1) 
	{
		
		DiamondsTogether(gridPosition.x, gridPosition.y);
	}
	if (oscaretmato)
	{
		currentAnim = &togetherAllAnim;
	}
	
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Block::Update();
}

void Block_Diamond::BlockTogether()
{
	oscaretmato = 1;
}
void Block_Diamond::DiamondsTogether(int x, int y)
{
	if (App->blocks->DiamondInGridPosition(x - 1, y) && App->blocks->DiamondInGridPosition(x + 1, y) == 1
		||
		App->blocks->DiamondInGridPosition(x, y - 1) && App->blocks->DiamondInGridPosition(x, y + 1) == 1)
	{
		//anim
		//printf("1000 PUNTS");
		currentAnim = &togetherAllAnim;
		App->score->AddScore(10000);
		Dia = 0;
	}
};
