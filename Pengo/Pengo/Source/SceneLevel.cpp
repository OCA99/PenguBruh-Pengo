#include "SceneLevel.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
//#include "ModuleCollisions.h"
//#include "ModuleEnemies.h"
#include "ModulePlayer.h"

SceneLevel::SceneLevel(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel::~SceneLevel()
{

}

// Load assets
bool SceneLevel::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->Enable();

	return ret;
}

#include <iostream>

Update_Status SceneLevel::Update()
{
	return Update_Status::UPDATE_CONTINUE;
	timer += 1 / 60;
	std::cout << timer << std::endl;
}

// Update: draw background
Update_Status SceneLevel::PostUpdate()
{
	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel::CleanUp()
{
	App->player->Disable();

	return true;
}