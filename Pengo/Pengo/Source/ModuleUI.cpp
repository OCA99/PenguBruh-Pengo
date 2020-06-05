#include "ModuleUI.h"

#include "Application.h"
#include "ModuleFonts.h"
#include "Score.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleBlocks.h"

#include <iostream>

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

	texture = App->textures->Load("assets/sprites/Miscellaneous.png");

	life.GenerateAnimation({ 0, 152, 16, 14 }, 1, 1);
	egg.GenerateAnimation({ 80, 82, 8, 8 }, 1, 1);
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

Update_Status ModuleUI::PostUpdate()
{
	App->fonts->BlitText(8, 0, blueFontID, "1P");
	int score = App->score->GetScore();
	char scoreText[DYNAMIC_TEXT_LEN + 1];

	intToString(scoreText, score);
	RenderDynamicText(scoreText, 64, 0, whiteFontID, true);

	App->fonts->BlitText(80, 0, blueFontID, "HI");

	int highScore = App->score->GetHighscore();
	char highScoreText[DYNAMIC_TEXT_LEN + 1];

	intToString(highScoreText, highScore);
	RenderDynamicText(highScoreText, 136, 0, whiteFontID, true);

	if (App->player->lifes > 1) App->render->Blit(texture, 0, 10, &life.GetCurrentFrame());
	if (App->player->lifes > 2) App->render->Blit(texture, 18, 10, &life.GetCurrentFrame());
	if (App->player->lifes > 3) App->render->Blit(texture, 36, 10, &life.GetCurrentFrame());

	if (App->blocks->remainingEggs > 0) App->render->Blit(texture, 112, 16, &egg.GetCurrentFrame());
	if (App->blocks->remainingEggs > 1) App->render->Blit(texture, 120, 16, &egg.GetCurrentFrame());
	if (App->blocks->remainingEggs > 2) App->render->Blit(texture, 128, 16, &egg.GetCurrentFrame());
	if (App->blocks->remainingEggs > 3) App->render->Blit(texture, 136, 16, &egg.GetCurrentFrame());

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
	int i = 0;
	for (; i < DYNAMIC_TEXT_LEN; i++) {
		if (text[i] != '0') break;
	}
	if (i == DYNAMIC_TEXT_LEN) {
		App->fonts->BlitText(x - (inverse ? (DYNAMIC_TEXT_LEN - i) * 9 : 0), y, fontIndex, "0");
	}
	else {
		App->fonts->BlitText(x - (inverse ? (DYNAMIC_TEXT_LEN - 1 - i) * 9 : 0), y, fontIndex, text + i);
	}
}