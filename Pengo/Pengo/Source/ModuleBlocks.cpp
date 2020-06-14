#include "ModuleBlocks.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

#include "Block.h"
#include "Block_Normal.h"
#include "Block_Diamond.h"
#include "Block_Egg.h"

ModuleBlocks::ModuleBlocks(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_BLOCKS; ++i)
		blocks[i] = nullptr;
}

ModuleBlocks::~ModuleBlocks()
{

}

bool ModuleBlocks::Start()
{
	texture = App->textures->Load("assets/sprites/stages.png");
	remainingEggs = 0;
	diamondsDone = false;
	return true;
}


Update_Status ModuleBlocks::PreUpdate()
{
	// Remove all enemies scheduled for deletion
	for (uint i = 0; i < MAX_BLOCKS; ++i)
	{
		if (blocks[i] != nullptr && blocks[i]->pendingToDelete)
		{
			delete blocks[i];
			blocks[i] = nullptr;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleBlocks::Update()
{

	for (uint i = 0; i < MAX_BLOCKS; ++i)
	{
		if (blocks[i] != nullptr) {
			blocks[i]->Update();
		}
	}


	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleBlocks::PostUpdate()
{
	for (uint i = 0; i < MAX_BLOCKS; ++i)
	{
		if (blocks[i] != nullptr) {
			blocks[i]->Draw();
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleBlocks::CleanUp()
{
	LOG("Freeing all blocks");

	for(uint i = 0; i < MAX_BLOCKS; ++i)
	{
		if(blocks[i] != nullptr)
		{
			delete blocks[i];
			blocks[i] = nullptr;
		}
	}

	App->textures->Unload(texture);

	return true;
}


void ModuleBlocks::AddBlock(Block_Type type, int x, int y)
{
	for (uint i = 0; i < MAX_BLOCKS; ++i)
	{
		if (blocks[i] == nullptr)
		{
			switch (type)
			{
				case Block_Type::NORMAL:
					blocks[i] = new Block_Normal(x, y);
					break;
				case Block_Type::DIAMOND:
					blocks[i] = new Block_Diamond(x, y);
					break;
				case Block_Type::EGG:
					blocks[i] = new Block_Egg(x, y, eggColor);
					remainingEggs++;
					break;
			}
			blocks[i]->texture = texture;
			break;
		}
	}
	maxEggs = remainingEggs;
}

bool ModuleBlocks::BlockInGridPosition(int x, int y) {
	for (uint i = 0; i < MAX_BLOCKS; ++i)
	{
		if (blocks[i] != nullptr)
		{
			if (blocks[i]->gridPosition.x == x && blocks[i]->gridPosition.y == y) return true;
		}
	}
	return false;
}

bool ModuleBlocks::DiamondInGridPosition(int x, int y) {
	for (uint i = 0; i < MAX_BLOCKS; ++i)
	{
		if (blocks[i] != nullptr)
		{
			if (blocks[i]->type == Block::Block_Type::DIAMOND)
			{
				if (blocks[i]->gridPosition.x == x && blocks[i]->gridPosition.y == y) return true;
			}
			
		}
	}
	return false;
}

void ModuleBlocks::PushBlock(int fromx, int fromy, int x, int y) {
	for (uint i = 0; i < MAX_BLOCKS; ++i)
	{
		if (blocks[i] != nullptr)
		{
			if (blocks[i]->gridPosition.x == x && blocks[i]->gridPosition.y == y) {
				if (!blocks[i]->destroying) blocks[i]->Pushed(fromx, fromy);
			}
		}
	}
}

void ModuleBlocks::DestroyBlock(int x, int y) {
	for (uint i = 0; i < MAX_BLOCKS; ++i)
	{
		if (blocks[i] != nullptr)
		{
			if (blocks[i]->gridPosition.x == x && blocks[i]->gridPosition.y == y) {
				if (blocks[i]->type == Block::Block_Type::EGG) {
					App->blocks->remainingEggs--;
				}
				delete blocks[i];
				blocks[i] = nullptr;
			}
		}
	}
}

bool ModuleBlocks::DestructibleByEnemy(int x, int y) {
	for (uint i = 0; i < MAX_BLOCKS; ++i)
	{
		if (blocks[i] != nullptr)
		{
			if (blocks[i]->gridPosition.x == x && blocks[i]->gridPosition.y == y) {
				return blocks[i]->type == Block::Block_Type::NORMAL && blocks[i]->destroying == false && !blocks[i]->isMoving();
			}
		}
	}
	return false;
}

void ModuleBlocks::BreakBlock(int x, int y) {
	for (uint i = 0; i < MAX_BLOCKS; ++i)
	{
		if (blocks[i] != nullptr)
		{
			if (blocks[i]->gridPosition.x == x && blocks[i]->gridPosition.y == y) {
				blocks[i]->destroy();
			}
		}
	}
}

bool ModuleBlocks::PositionInMap(int x, int y) {
	if (x < 0) return false;
	if (x > 12) return false;
	if (y < 0) return false;
	if (y > 14) return false;
	return true;
}

void ModuleBlocks::HatchNextEgg()
{
	if (waitToHatch > 0) {
		waitToHatch--;
		return;
	}
	for (uint i = 0; i < MAX_BLOCKS; ++i)
	{
		if (blocks[i] != nullptr)
		{
			if (blocks[i]->type == Block::Block_Type::EGG)
			{
				Block_Egg* b = (Block_Egg*)blocks[i];
				if (b->hatching || b->hatched) continue;
				b->NextBlobSpawn();
				break;
			}
		}
	}
}