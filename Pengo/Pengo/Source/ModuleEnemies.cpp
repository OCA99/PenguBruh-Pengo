#include "ModuleEnemies.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleBlocks.h"


#include "Enemy.h"

ModuleEnemies::ModuleEnemies(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

ModuleEnemies::~ModuleEnemies()
{
	
}

bool ModuleEnemies::Start()
{
	texture = App->textures->Load("assets/sprites/pengos.png");
	fx_once = true;
	winCounter = 0;
	
	std::random_device generator;

	std::uniform_int_distribution<int> distribution(0, 7);

	color = distribution(generator);

	return true;
}


Update_Status ModuleEnemies::PreUpdate()
{
	// Remove all enemies scheduled for deletion
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->pendingToDelete)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleEnemies::Update()
{
	//HandleEnemiesSpawn();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
			enemies[i]->Update();
	}

	//HandleEnemiesDespawn();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleEnemies::PostUpdate()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr) {
			enemies[i]->Draw();
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

void ModuleEnemies::AddEnemy(int x, int y)
{

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] == nullptr)
		{
			enemies[i] = new Enemy(x, y, color);
			enemies[i]->texture = texture;
			break;
		}
	}
}

bool ModuleEnemies::EnemyInGridPosition(int x, int y) {
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			if (enemies[i]->gridPosition.x == x && enemies[i]->gridPosition.y == y && !enemies[i]->stunned) return true;
		}
	}
	return false;
}

int ModuleEnemies::PushEnemy(int fromx, int fromy, int x, int y) {
	int pushedEnemies = 0;
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			if (enemies[i]->gridPosition.x == x && enemies[i]->gridPosition.y == y) {
				if (!enemies[i]->pushed) pushedEnemies++;
				enemies[i]->Pushed(fromx, fromy);
			}
		}
	}
	return pushedEnemies;
}

bool ModuleEnemies::VictoryCheck(bool win)
{
	//Check if there are enemies on screen. If = 0 then win
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr) winCounter++;
		
	}

	/*if (winCounter == 1 && fx_once == true)
	{
		//App->audio->PlayFx(8, 0);
		//fx_once = false;
	}*/

	if (winCounter != 0) {
		winCounter = 0;
	}
	else {
		win = true;
	}

	return win;
}

void ModuleEnemies::WallPushed(int wallID)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			enemies[i]->WallStunned(wallID);
		}
	}
}

void ModuleEnemies::Reset() {
	int count = 0;
	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		if (enemies[i] != nullptr) {
			enemies[i]->stunned = false;
			switch (count) {
			case 0:
				if (App->blocks->BlockInGridPosition(0, 0)) {
					App->blocks->DestroyBlock(0, 0);
				}
				enemies[i]->SetPosition(0, 0);
				enemies[i]->GetNextTargetTile();
				enemies[i]->UnSuicide();
				break;
			case 1:
				if (App->blocks->BlockInGridPosition(12, 0)) {
					App->blocks->DestroyBlock(12, 0);
				}
				enemies[i]->SetPosition(12, 0);
				enemies[i]->GetNextTargetTile();
				enemies[i]->UnSuicide();
				break;
			case 2:
				if (App->blocks->BlockInGridPosition(0, 14)) {
					App->blocks->DestroyBlock(0, 14);
				}
				enemies[i]->SetPosition(0, 14);
				enemies[i]->GetNextTargetTile();
				enemies[i]->UnSuicide();
				break;
			case 3:
				if (App->blocks->BlockInGridPosition(12, 14)) {
					App->blocks->DestroyBlock(12, 14);
				}
				enemies[i]->SetPosition(12, 14);
				enemies[i]->GetNextTargetTile();
				enemies[i]->UnSuicide();
				break;
			default:
				delete enemies[i];
				enemies[i] = nullptr;
				break;
			}
			count++;
		}
	}
}

void ModuleEnemies::NextColor() {
	color++;
	color = color % 7;
}

void ModuleEnemies::Suicide() {
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			enemies[i]->Suicide();
		}
	}
}