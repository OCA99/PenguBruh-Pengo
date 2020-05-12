#include "ModuleWalls.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

#include "Wall.h"
#include "WallHorizontal.h"
#include "WallVertical.h"

#include "ModuleEnemies.h"

ModuleWalls::ModuleWalls(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_WALLS; ++i)
		walls[i] = nullptr;
}

ModuleWalls::~ModuleWalls()
{

}

bool ModuleWalls::Start()
{
	texture = App->textures->Load("assets/sprites/stages.png");
	return true;
}


Update_Status ModuleWalls::PreUpdate()
{

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleWalls::Update()
{

	for (uint i = 0; i < MAX_WALLS; ++i)
	{
		if (walls[i] != nullptr) {
			walls[i]->Update();
		}
	}


	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleWalls::PostUpdate()
{
	for (uint i = 0; i < MAX_WALLS; ++i)
	{
		if (walls[i] != nullptr) {
			walls[i]->Draw();
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleWalls::CleanUp()
{
	LOG("Freeing all walls");

	for (uint i = 0; i < MAX_WALLS; ++i)
	{
		if (walls[i] != nullptr)
		{
			delete walls[i];
			walls[i] = nullptr;
		}
	}

	return true;
}

void ModuleWalls::AddWall(Wall_Type type, int x, int y)
{
	for (uint i = 0; i < MAX_WALLS; ++i)
	{
		if (walls[i] == nullptr)
		{
			switch (type)
			{
			case Wall_Type::HORIZONTAL:
				walls[i] = new WallHorizontal(x, y);
				break;
			case Wall_Type::VERTICAL:
				walls[i] = new WallVertical(x, y);
				break;
			}
			walls[i]->texture = texture;
			break;
		}
	}
}

void ModuleWalls::PushWall(int i) {

	if (walls[i] != nullptr) {
		switch (i) {
		case 0:
			App->enemies->WallPushed(i);
			break;
		case 1:
			App->enemies->WallPushed(i);
			break;
		case 2:
			App->enemies->WallPushed(i);
			break;
		case 3:
			App->enemies->WallPushed(i);
			break;
		default:
			break;
		}

		walls[i]->Shake();
		App->audio->PlayFx(10, 0);
	}
}