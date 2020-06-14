#include "SceneMenu.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Score.h"
#include "ModulePlayer.h"

SceneMenu::SceneMenu(bool startEnabled) : Module(startEnabled)
{

}

SceneMenu::~SceneMenu()
{

}

// Load assets
bool SceneMenu::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("assets/sprites/menusprites.png");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->score->ResetScore();

	return ret;
}

Update_Status SceneMenu::Update()
{
	GamePad& pad = App->input->pads[0];

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || pad.a == true)
	{
		App->gameTime = 0.0f;
		App->player->lifes = 3;
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneMenu::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneMenu::CleanUp()
{
	App->textures->Unload(bgTexture);

	return true;
}
