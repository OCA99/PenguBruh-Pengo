#include "ScenePoints.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Score.h"

#include "ModuleUI.h"


ScenePoints::ScenePoints(bool startEnabled) : Module(startEnabled)
{

}

ScenePoints::~ScenePoints()
{

}


bool ScenePoints::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("assets/sprites/menusprites.png");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}


Update_Status ScenePoints::Update() {
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneMenu, 90);
	}

	return Update_Status::UPDATE_CONTINUE;
}
Update_Status ScenePoints::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}

bool ScenePoints::CleanUp()
{

	return true;
}
