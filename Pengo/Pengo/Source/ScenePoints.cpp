#include "ScenePoints.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Score.h"

#include "ModuleFonts.h"
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


	App->render->camera.x = 0;
	App->render->camera.y = 0;

	//fonts
	char lookupTable[] = { "0123456789.,\"!'-©ABCDEFGHIJKLMNOPQRSTUVWXYZ.    " };
	whiteFontID = App->fonts->Load("assets/sprites/Fonts/white.png", lookupTable, 3);
	blueFontID = App->fonts->Load("assets/sprites/Fonts/blue.png", lookupTable, 3);
	yellowFontID = App->fonts->Load("assets/sprites/Fonts/yellow.png", lookupTable, 3);

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

	App->fonts->BlitText(16, 32, yellowFontID, "GAME TIME");

	return Update_Status::UPDATE_CONTINUE;
}

bool ScenePoints::CleanUp()
{
	App->fonts->UnLoad(whiteFontID);
	App->fonts->UnLoad(blueFontID);


	return true;
}
