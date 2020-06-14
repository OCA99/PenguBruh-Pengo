#define _CRT_SECURE_NO_WARNINGS

#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleDebug.h"
#include "ModuleInput.h"
#include "Application.h"
#include "ModuleFadeToBlack.h"
#include "Block.h"
#include "ModulePlayer.h"
#include "ModuleBlocks.h"
#include "ModuleEnemies.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL.h"
#include "ModuleFonts.h"
#include "ModuleUI.h"

ModuleDebug::ModuleDebug(bool startEnabled) : Module(startEnabled)
{

}


ModuleDebug::~ModuleDebug()
{

}

bool ModuleDebug::Init()
{
	return true;
}

bool ModuleDebug::Start()
{
	char lookupTable[] = { "0123456789.,\"!'-©ABCDEFGHIJKLMNOPQRSTUVWXYZ.    " };
	whiteFontID = App->fonts->Load("assets/sprites/Fonts/white.png", lookupTable, 3);
	yellowFontID = App->fonts->Load("assets/sprites/Fonts/yellow.png", lookupTable, 3);

	return true;
}

Update_Status ModuleDebug::PreUpdate()
{
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleDebug::Update()
{
	if (App->input->keys[SDL_SCANCODE_F] == Key_State::KEY_DOWN)
	{
		if (DEBUG_MODE == 0)
		{
			DEBUG_MODE = 1;
		}
		else
		{
			GMODE = 0;
			DEBUG_MODE = 0;
		}
	}
	if (App->input->keys[SDL_SCANCODE_G] == Key_State::KEY_DOWN)
	{
		if (DEBUG_MODE == 1)
		{
			if (GMODE == 0)
			{
				GMODE = 1;
			}
			else
			{
				GMODE = 0;
			}
		}
	}
	if (App->input->keys[SDL_SCANCODE_M] == Key_State::KEY_DOWN)
	{
		if (memory == 0)
		{
			memory = 1;
		}
		else
		{
			memory = 0;
		}
	}

	if (App->input->keys[SDL_SCANCODE_ESCAPE] == Key_State::KEY_DOWN)
	{
		return Update_Status::UPDATE_STOP;
	}

	if (DEBUG_MODE == 1)
	{
		if (App->input->keys[SDL_SCANCODE_K] == Key_State::KEY_DOWN)
		{
			App->player->dead = true;
			App->player->currentAnimation = &App->player->dieAnim;
			App->enemies->Pause();
		}

		if (App->input->keys[SDL_SCANCODE_LSHIFT] == Key_State::KEY_DOWN)
		{
			if (App->player->lifes != 3)
			{
				App->player->lifes++;
			}
		}


		if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_DOWN)
		{
			ascending = true;
		}
		if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_DOWN)
		{
			descending = true;
		}

	}

	
	
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleDebug::PostUpdate()
{
	if (memory) {
		char currentTextures[10];
		App->ui->intToString(currentTextures, App->textures->k);
		App->ui->RenderDynamicText(currentTextures, 214, 2, whiteFontID, true);

		char currentFx[10];
		App->ui->intToString(currentFx, App->audio->k);
		App->ui->RenderDynamicText(currentFx, 214, 11, whiteFontID, true);

		App->fonts->BlitText(120, 2, whiteFontID, "TEXTURES");
		App->fonts->BlitText(121, 11, whiteFontID, "FX");

	}

	if (GMODE) {
		App->fonts->BlitText(208, 280, yellowFontID, "G");
	}

	if (DEBUG_MODE) {
		App->fonts->BlitText(198, 280, yellowFontID, "F");
	}

	return Update_Status::UPDATE_CONTINUE;
}

bool ModuleDebug::CleanUp()
{
	App->fonts->UnLoad(whiteFontID);
	App->fonts->UnLoad(yellowFontID);
	return true;
}

void ModuleDebug::Enable()
{
	if (!isEnabled)
	{
		isEnabled = true;
		Start();
	}
}
int ModuleDebug::CanPut(int x, int y)
{
	int a = x;
	int b = y;
	canput = 1;
	if (App->enemies->EnemyInGridPosition(a,b))
	{
		
		canput = 0;
	}
	else if (App->blocks->BlockInGridPosition(a, b))
	{
		
		canput = 0;
	}
	else if ( x > 12 || y > 14 || x < 0 || y < 0)
	{
		
		canput = 0;
	}
	else if (App->player->gridPosition.x == a && App->player->gridPosition.y == b)
	{
		
		canput = 0;
	}
	
	return canput;
}
void ModuleDebug::BlockOnMap(int x, int y)
{
	if (App->debug->DEBUG_MODE == 1)
	{
		int gridposX = ((x - 8) / 16);
		int gridposY = ((y - 32) / 16);
		if (CanPut(gridposX, gridposY) == 1)
		{

			App->blocks->AddBlock(Block_Type::NORMAL, gridposX, gridposY);
		}
	}
	
}
void ModuleDebug::DiamondOnMap(int x, int y)
{
	if (App->debug->DEBUG_MODE == 1)
	{
		int gridposX = ((x - 8) / 16);
		int gridposY = ((y - 32) / 16);
		if (CanPut(gridposX, gridposY) == 1)
		{
			App->blocks->AddBlock(Block_Type::DIAMOND, gridposX, gridposY);
		}
	}

}
void ModuleDebug::EggOnMap(int x, int y)
{
	if (App->debug->DEBUG_MODE == 1)
	{
		int gridposX = ((x - 8) / 16);
		int gridposY = ((y - 32) / 16);
		if (CanPut(gridposX, gridposY) == 1)
		{
			App->blocks->AddBlock(Block_Type::EGG, gridposX, gridposY);
		}
	}

}
void ModuleDebug::SnoBeeOnMap(int x, int y)
{
	if (App->debug->DEBUG_MODE == 1)
	{
		int gridposX = (x - 8) / 16;
		int gridposY = (y - 32) / 16;
		if (CanPut(gridposX, gridposY) == 1)
		{
			App->enemies->AddEnemy(gridposX, gridposY);
		}
	}

	
}
void ModuleDebug::DestroyBlock(int x, int y)
{
	if (App->debug->DEBUG_MODE == 1)
	{
		int gridposX = (x - 8) / 16;
		int gridposY = (y - 32) / 16;
		if (CanPut(gridposX, gridposY) == 0)
		{
			App->blocks->DestroyBlock(gridposX, gridposY);
		}
	}
}

void ModuleDebug::Disable()
{
	if (isEnabled)
	{
		isEnabled = false;
		CleanUp();
	}
}


