#include "SceneLevel.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleEnemies.h"
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

Update_Status SceneLevel::Update()
{
	if (!App->player->hasDied && !App->enemies->enemyHasDied) timer += 1.0f / 60.0f;
	if (timer > 120.0f) {
		App->enemies->Suicide();
	}
	App->gameTime += 1.0f / 60.0f;
	return Update_Status::UPDATE_CONTINUE;
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