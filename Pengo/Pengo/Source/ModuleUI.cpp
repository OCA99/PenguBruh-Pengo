#include "ModuleUI.h"
#include "ModuleAudio.h"
#include "Application.h"
#include "ModuleFonts.h"
#include "Score.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleBlocks.h"

ModuleUI::ModuleUI(bool startEnabled) : Module(startEnabled)
{
}

ModuleUI::~ModuleUI()
{
}

bool ModuleUI::Init() {

	life.GenerateAnimation({ 0, 152, 16, 14 }, 1, 1);
	egg.GenerateAnimation({ 80, 82, 16, 8 }, 1, 2);
	egg.loop = true;
	egg.speed = 0.05f;
	eggFX.GenerateAnimation({ 100, 83, 7, 7 }, 1, 1);
	eggFX.speed = 0.05f;
	levelFlag.GenerateAnimation({ 54, 151, 15, 15 }, 1, 1);
	levelFlag5.GenerateAnimation({ 73, 151, 15, 15 }, 1, 1);
	return true;
}

bool ModuleUI::Start() {
	char lookupTable[] = { "0123456789.,\"!'-©ABCDEFGHIJKLMNOPQRSTUVWXYZ.    " };
	whiteFontID = App->fonts->Load("assets/sprites/Fonts/white.png", lookupTable, 3);
	blueFontID = App->fonts->Load("assets/sprites/Fonts/blue.png", lookupTable, 3);
	yellowFontID = App->fonts->Load("assets/sprites/Fonts/yellow.png", lookupTable, 3);

	texture = App->textures->Load("assets/sprites/Miscellaneous.png");
	return true;
}

bool ModuleUI::CleanUp() {

	App->fonts->UnLoad(whiteFontID);
	App->fonts->UnLoad(blueFontID);
	App->fonts->UnLoad(yellowFontID);
	App->textures->Unload(texture);

	return true;
}

Update_Status ModuleUI::PreUpdate()
{
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleUI::Update()
{
	egg.Update();
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
	if (App->blocks->remainingEggs = 1) App->render->Blit(texture, 120, 16, &eggFX.GetCurrentFrame());
	if (App->blocks->remainingEggs > 1) App->render->Blit(texture, 120, 16, &egg.GetCurrentFrame());
	if (App->blocks->remainingEggs = 2) App->render->Blit(texture, 128, 16, &eggFX.GetCurrentFrame());
	if (App->blocks->remainingEggs > 2) App->render->Blit(texture, 128, 16, &egg.GetCurrentFrame());
	if (App->blocks->remainingEggs = 3) App->render->Blit(texture, 136, 16, &eggFX.GetCurrentFrame());
	if (App->blocks->remainingEggs > 3) App->render->Blit(texture, 136, 16, &egg.GetCurrentFrame());
	if (App->blocks->remainingEggs = 4) App->render->Blit(texture, 144, 16, &eggFX.GetCurrentFrame());
	if (App->blocks->remainingEggs > 4) App->render->Blit(texture, 144, 16, &egg.GetCurrentFrame());
	if (App->blocks->remainingEggs = 5) App->render->Blit(texture, 152, 16, &eggFX.GetCurrentFrame());
	if (App->blocks->remainingEggs > 5) App->render->Blit(texture, 152, 16, &egg.GetCurrentFrame());
	if (App->blocks->remainingEggs = 6) App->render->Blit(texture, 160, 16, &eggFX.GetCurrentFrame());
	if (App->blocks->remainingEggs > 6) App->render->Blit(texture, 160, 16, &egg.GetCurrentFrame());
	if (App->blocks->remainingEggs = 7) App->render->Blit(texture, 168, 16, &eggFX.GetCurrentFrame());
	if (App->blocks->remainingEggs > 7) App->render->Blit(texture, 168, 16, &egg.GetCurrentFrame());

	App->fonts->BlitText(8, 280, whiteFontID, "ACT");
	char currentLvlText[DYNAMIC_TEXT_LEN + 1];
	intToString(currentLvlText, App->levelNum);
	RenderDynamicText(currentLvlText, 45, 280, whiteFontID, true);

	int level5 = App->levelNum / 5;
	int remain = App->levelNum % 5;

	int x = 56;
	int y = 273;

	for (int i = 0; i < level5; i++) {
		App->render->Blit(texture, x, y, &levelFlag5.GetCurrentFrame());
		x += 16;
	}

	for (int i = 0; i < remain; i++) {
		App->render->Blit(texture, x, y, &levelFlag.GetCurrentFrame());
		x += 14;
	}

	if (showingBonus) {
		showingCounter += 1.0f / 60.0f;

		App->render->DrawQuad({ 72, 136, 80, 48 }, 0, 0, 0, 255);
		App->fonts->BlitText(80, 144, yellowFontID, "BONUS");
		
		char remainingBonusText[DYNAMIC_TEXT_LEN + 1];
		intToString(remainingBonusText, remainingBonus);
		RenderDynamicText(remainingBonusText, 124, 152, whiteFontID, true);

		App->fonts->BlitText(116, 160, whiteFontID, "PTS.");
		

		if (remainingBonus > 0 && showingCounter >= 1.0f) {
			remainingBonus -= 100;
			if (fx == true)
			{
				App->audio->PlayFx(3, 0);
				fx = false;
			}
			App->score->AddScore(100);
		}

		if (showingCounter >= 5.0f) {
			showingCounter = 0.0f;
			showingBonus = false;
		}

		

	}

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

void ModuleUI::Bonus(int points) {
	if (showingBonus) return;
	remainingBonus = (float)points;
	showingBonus = true;
}
