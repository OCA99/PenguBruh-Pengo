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
	twogetherAnim.speed = 0.085f;
	twogetherAnim.loop = true;

	type = Block_Type::DIAMOND;
}

void Block_Diamond::Update()
{
	if (App->blocks->allTogether != true)
	{
		FirstDiamondTogether(gridPosition.x, gridPosition.y);
	}
		DiamondsTogether(gridPosition.x, gridPosition.y);

	
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Block::Update();
}


void Block_Diamond::DiamondsTogether(int x, int y)
{

		if (App->blocks->DiamondInGridPosition(x - 1, y) && App->blocks->DiamondInGridPosition(x + 1, y) == true
			||
			App->blocks->DiamondInGridPosition(x, y - 1) && App->blocks->DiamondInGridPosition(x, y + 1) == true)
		{
			printf("lavaina\n");
			//anim
			//printf("1000 PUNTS");
			connected = true;
			App->blocks->allTogether = true;
			if (pointsOnce != true)
			{
				pointsOnce = true;
				App->score->AddScore(10000);
			}
		} 

		if (connected = true)
		{
			if (App->blocks->DiamondInGridPosition(x - 1, y) && App->blocks->DiamondInGridPosition(x + 1, y) &&
				App->blocks->DiamondInGridPosition(x, y - 1) && App->blocks->DiamondInGridPosition(x, y + 1) == false)
			{
				connected = false;
				App->blocks->disconnected = true;
				App->blocks->allTogether = false;
				pointsOnce = false;
			}
		}

		if (App->blocks->allTogether == true)
		{
			currentAnim = &togetherAllAnim;
		} else if (App->blocks->allTogether == false && App->blocks->disconnected != true)
		{
			currentAnim = &normalAnim;
		}
};

void Block_Diamond::FirstDiamondTogether(int x, int y)
{
	if ((App->blocks->DiamondInGridPosition(x - 1, y) == true ) || (App->blocks->DiamondInGridPosition(x + 1, y) == true)
		||
		(App->blocks->DiamondInGridPosition(x, y - 1) == true )|| (App->blocks->DiamondInGridPosition(x, y + 1) == true))
	{
		connected = true;
		App->blocks->twoTogether = true;
	}

	if (connected == true)
	{
		printf("haentrao");
		if (App->blocks->DiamondInGridPosition(x - 1, y) && App->blocks->DiamondInGridPosition(x + 1, y) &&
			App->blocks->DiamondInGridPosition(x, y - 1) && App->blocks->DiamondInGridPosition(x, y + 1) == false)
		{
			printf("%d", disconnected);
			connected = false;
			App->blocks->twoTogether = false;
			App->blocks->disconnected = false;
		}
	}

	if (App->blocks->twoTogether == true)
	{
		currentAnim = &twogetherAnim;
	}
	
	

	if (App->blocks->disconnected == false)
	{
		currentAnim = &normalAnim;
	}
}