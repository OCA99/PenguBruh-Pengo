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
void ScenePoints::intToString(char* buffer, int k) {

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

void ScenePoints::RenderDynamicText(char* text, int x, int y, int fontIndex, bool inverse) {
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

	App->fonts->BlitText(8, 32, yellowFontID, "GAME TIME");

	int time = App->gameTime;
	int minutes = time / 60;
	int seconds = time % 60;

	char minutesText[DYNAMIC_TEXT_LEN + 1];
	intToString(minutesText, minutes);
	RenderDynamicText(minutesText, 104, 32, whiteFontID, true);

	App->fonts->BlitText(119, 32, yellowFontID, "MIN.");

	char secondsText[DYNAMIC_TEXT_LEN + 1];
	intToString(secondsText, seconds);
	RenderDynamicText(secondsText, 170, 32, whiteFontID, true);

	App->fonts->BlitText(183, 32, yellowFontID, "SEC.");

	App->fonts->BlitText(46, 100, blueFontID, "1P");
	int score = App->score->GetScore();
	char scoreText[DYNAMIC_TEXT_LEN + 1];

	intToString(scoreText, score);
	RenderDynamicText(scoreText, 100, 100, whiteFontID, true);

	App->fonts->BlitText(116, 100, blueFontID, "HI");

	int highScore = App->score->GetHighscore();
	char highScoreText[DYNAMIC_TEXT_LEN + 1];

	intToString(highScoreText, highScore);
	RenderDynamicText(highScoreText, 172, 100, whiteFontID, true);

	App->fonts->BlitText(30, 150, whiteFontID, "THANKS FOR PLAYING!");

	return Update_Status::UPDATE_CONTINUE;
}

bool ScenePoints::CleanUp()
{
	App->fonts->UnLoad(whiteFontID);
	App->fonts->UnLoad(blueFontID);
	App->fonts->UnLoad(yellowFontID);


	return true;
}
