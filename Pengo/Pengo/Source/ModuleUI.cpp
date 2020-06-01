#include "ModuleUI.h"

#include "Application.h"
#include "ModuleFonts.h"
#include "Score.h"

#include "SDL/include/SDL_render.h"

ModuleUI::ModuleUI(bool startEnabled) : Module(startEnabled)
{
}

ModuleUI::~ModuleUI()
{
}

bool ModuleUI::Init() {

	return true;
}

bool ModuleUI::Start() {
	char lookupTable[] = { "0123456789.,\"!'-©ABCDEFGHIJKLMNOPQRSTUVWXYZ.    " };
	whiteFontID = App->fonts->Load("assets/sprites/Fonts/white.png", lookupTable, 3);
	blueFontID = App->fonts->Load("assets/sprites/Fonts/blue.png", lookupTable, 3);
	return true;
}

bool ModuleUI::CleanUp() {
	return true;
}

Update_Status ModuleUI::PreUpdate()
{
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleUI::Update()
{
	return Update_Status::UPDATE_CONTINUE;
}

#include <iostream>

Update_Status ModuleUI::PostUpdate()
{
	App->fonts->BlitText(8, 0, blueFontID, "1P");
	int score = App->score->GetScore();
	char scoreText[DYNAMIC_TEXT_LEN + 1];

	intToString(scoreText, score);
	RenderDynamicText(scoreText, 64, 0, whiteFontID, true);

	return Update_Status::UPDATE_CONTINUE;
}

void ModuleUI::intToString(char* buffer, int k) {

	for (int i = 0; i < DYNAMIC_TEXT_LEN; i++) {
		buffer[i] = '0';
	}

	buffer[DYNAMIC_TEXT_LEN] = 0;

	int i = DYNAMIC_TEXT_LEN - 1;
	while (k != 0) {
		if (i < 0) break;
		buffer[i--] += k % 10;
		k /= 10;
	}
}

void ModuleUI::RenderDynamicText(char* text, int x, int y, int fontIndex, bool inverse) {
	App->fonts->BlitText(x - (inverse ? (DYNAMIC_TEXT_LEN - 1) * 9 : 0), y, fontIndex, text);
}