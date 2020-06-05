#include "SceneLevel9.h"
#include "ModuleDebug.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
//#include "ModuleCollisions.h"
//#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleBlocks.h"
#include "ModuleWalls.h"
#include "ModuleEnemies.h"
#include "ModuleFadeToBlack.h"
#include "ModuleUI.h"

SceneLevel9::SceneLevel9(bool startEnabled) : SceneLevel(startEnabled)
{

}

SceneLevel9::~SceneLevel9()
{

}

// Load assets
bool SceneLevel9::Start()
{
	LOG("Loading background assets");
	App->audio->PlayFx(1, 0);
	App->player->Enable();
	App->blocks->Enable();
	App->walls->Enable();
	App->enemies->Enable();
	App->ui->Enable();

	App->enemies->NextColor();
	int color = App->enemies->GetColor();
	App->blocks->SetEggColor(color);
	App->levelNum = 9;

	bool ret = true;

	win = false;

	//bgTexture = App->textures->Load("Assets/Sprites/background.png");
	App->audio->PlayMusic("assets/Themes/Popcorn/Main BGM (Popcorn).ogg", 1.0f);

	App->enemies->AddEnemy(1, 1);
	App->enemies->AddEnemy(3, 11);
	App->enemies->AddEnemy(3, 13);
	App->enemies->AddEnemy(7, 3);

	//These are the enemies that will spawn inside a block (right coordinates)
	//App->enemies->AddEnemy(1, 9);
	//App->enemies->AddEnemy(3, 9);
	//App->enemies->AddEnemy(5, 1);
	//App->enemies->AddEnemy(9, 13);
	//App->enemies->AddEnemy(11, 6);
	//App->enemies->AddEnemy(11, 11);

	App->blocks->AddBlock(Block_Type::EGG, 1, 9);
	App->blocks->AddBlock(Block_Type::EGG, 3, 9);
	App->blocks->AddBlock(Block_Type::EGG, 5, 1);
	App->blocks->AddBlock(Block_Type::EGG, 9, 13);
	App->blocks->AddBlock(Block_Type::EGG, 11, 6);
	App->blocks->AddBlock(Block_Type::EGG, 11, 11);

	App->blocks->AddBlock(Block_Type::DIAMOND, 3, 5);
	App->blocks->AddBlock(Block_Type::DIAMOND, 5, 3);
	App->blocks->AddBlock(Block_Type::DIAMOND, 5, 5);

	App->audio->PlayFx(12, 0);

	App->blocks->AddBlock(Block_Type::NORMAL, 0, 3);
	App->blocks->AddBlock(Block_Type::NORMAL, 0, 11);
	App->blocks->AddBlock(Block_Type::NORMAL, 1, 0);
	App->blocks->AddBlock(Block_Type::NORMAL, 1, 3);
	App->blocks->AddBlock(Block_Type::NORMAL, 1, 5);
	App->blocks->AddBlock(Block_Type::NORMAL, 1, 7);
	App->blocks->AddBlock(Block_Type::NORMAL, 1, 8);
	App->blocks->AddBlock(Block_Type::NORMAL, 1, 11);
	App->blocks->AddBlock(Block_Type::NORMAL, 1, 12);
	App->blocks->AddBlock(Block_Type::NORMAL, 1, 13);
	App->blocks->AddBlock(Block_Type::NORMAL, 1, 14);
	App->blocks->AddBlock(Block_Type::NORMAL, 2, 5);
	App->blocks->AddBlock(Block_Type::NORMAL, 2, 9);
	App->blocks->AddBlock(Block_Type::NORMAL, 2, 11);
	App->blocks->AddBlock(Block_Type::NORMAL, 2, 13);
	App->blocks->AddBlock(Block_Type::NORMAL, 3, 0);
	App->blocks->AddBlock(Block_Type::NORMAL, 3, 1);
	App->blocks->AddBlock(Block_Type::NORMAL, 3, 2);
	App->blocks->AddBlock(Block_Type::NORMAL, 3, 3);
	App->blocks->AddBlock(Block_Type::NORMAL, 3, 4);
	App->blocks->AddBlock(Block_Type::NORMAL, 3, 6);
	App->blocks->AddBlock(Block_Type::NORMAL, 3, 7);
	App->blocks->AddBlock(Block_Type::NORMAL, 3, 8);
	App->blocks->AddBlock(Block_Type::NORMAL, 5, 6);
	App->blocks->AddBlock(Block_Type::NORMAL, 4, 11);
	App->blocks->AddBlock(Block_Type::NORMAL, 5, 2);
	App->blocks->AddBlock(Block_Type::NORMAL, 5, 7);
	App->blocks->AddBlock(Block_Type::NORMAL, 5, 8);
	App->blocks->AddBlock(Block_Type::NORMAL, 5, 9);
	App->blocks->AddBlock(Block_Type::NORMAL, 5, 10);
	App->blocks->AddBlock(Block_Type::NORMAL, 5, 11);
	App->blocks->AddBlock(Block_Type::NORMAL, 5, 12);
	App->blocks->AddBlock(Block_Type::NORMAL, 5, 13);
	App->blocks->AddBlock(Block_Type::NORMAL, 6, 1);
	App->blocks->AddBlock(Block_Type::NORMAL, 6, 3);
	App->blocks->AddBlock(Block_Type::NORMAL, 6, 7);
	App->blocks->AddBlock(Block_Type::NORMAL, 7, 1);
	App->blocks->AddBlock(Block_Type::NORMAL, 7, 4);
	App->blocks->AddBlock(Block_Type::NORMAL, 7, 5);
	App->blocks->AddBlock(Block_Type::NORMAL, 7, 7);
	App->blocks->AddBlock(Block_Type::NORMAL, 7, 8);
	App->blocks->AddBlock(Block_Type::NORMAL, 7, 9);
	App->blocks->AddBlock(Block_Type::NORMAL, 7, 10);
	App->blocks->AddBlock(Block_Type::NORMAL, 7, 11);
	App->blocks->AddBlock(Block_Type::NORMAL, 7, 13);
	App->blocks->AddBlock(Block_Type::NORMAL, 7, 14);
	App->blocks->AddBlock(Block_Type::NORMAL, 8, 3);
	App->blocks->AddBlock(Block_Type::NORMAL, 8, 7);
	App->blocks->AddBlock(Block_Type::NORMAL, 9, 0);
	App->blocks->AddBlock(Block_Type::NORMAL, 9, 1);
	App->blocks->AddBlock(Block_Type::NORMAL, 9, 2);
	App->blocks->AddBlock(Block_Type::NORMAL, 9, 3);
	App->blocks->AddBlock(Block_Type::NORMAL, 9, 5);
	App->blocks->AddBlock(Block_Type::NORMAL, 9, 7);
	App->blocks->AddBlock(Block_Type::NORMAL, 9, 8);
	App->blocks->AddBlock(Block_Type::NORMAL, 9, 9);
	App->blocks->AddBlock(Block_Type::NORMAL, 9, 10);
	App->blocks->AddBlock(Block_Type::NORMAL, 9, 11);
	App->blocks->AddBlock(Block_Type::NORMAL, 9, 12);
	App->blocks->AddBlock(Block_Type::NORMAL, 10, 3);
	App->blocks->AddBlock(Block_Type::NORMAL, 10, 5);
	App->blocks->AddBlock(Block_Type::NORMAL, 10, 13);
	App->blocks->AddBlock(Block_Type::NORMAL, 11, 1);
	App->blocks->AddBlock(Block_Type::NORMAL, 11, 3);
	App->blocks->AddBlock(Block_Type::NORMAL, 11, 4);
	App->blocks->AddBlock(Block_Type::NORMAL, 11, 5);
	App->blocks->AddBlock(Block_Type::NORMAL, 11, 6);
	App->blocks->AddBlock(Block_Type::NORMAL, 11, 7);
	App->blocks->AddBlock(Block_Type::NORMAL, 11, 8);
	App->blocks->AddBlock(Block_Type::NORMAL, 11, 9);
	App->blocks->AddBlock(Block_Type::NORMAL, 11, 10);
	App->blocks->AddBlock(Block_Type::NORMAL, 11, 13);
	App->blocks->AddBlock(Block_Type::NORMAL, 12, 1);

	App->walls->AddWall(Wall_Type::HORIZONTAL, 8, 24);
	App->walls->AddWall(Wall_Type::HORIZONTAL, 8, 272);
	App->walls->AddWall(Wall_Type::VERTICAL, 0, 24);
	App->walls->AddWall(Wall_Type::VERTICAL, 216, 24);


	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->currentLevel = this;

	return ret;
}


// Update: draw background
Update_Status SceneLevel9::PostUpdate()
{
	// Draw everything --------------------------------------
	//App->render->Blit(bgTexture, 0, 0, NULL);

	win = App->enemies->VictoryCheck(win);
	if (App->debug->GMODE == true)
	{
		if (App->debug->ascending == true)
		{
			App->debug->ascending = false;
			win = true;
		}
	}
	if (win)
	{
		App->fade->FadeToBlack((Module*)App->currentLevel, (Module*)App->sceneLevel_10, 90);
		App->audio->PlayFx(0, 0);
	}

	if (App->debug->GMODE == true)
	{
		if (App->debug->descending == true)
		{
			App->debug->descending = false;
			App->fade->FadeToBlack((Module*)App->currentLevel, (Module*)App->sceneLevel_8, 90);
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel9::CleanUp()
{
	App->player->Disable();
	App->blocks->Disable();
	App->walls->Disable();
	App->enemies->Disable();
	App->ui->Disable();

	return true;
}