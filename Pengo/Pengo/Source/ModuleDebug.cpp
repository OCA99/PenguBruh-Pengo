#define _CRT_SECURE_NO_WARNINGS

#include "Module.h"
#include "ModuleDebug.h"
#include "ModuleInput.h"
#include "Application.h"
#include "ModuleFadeToBlack.h"
#include "Block.h"
#include "ModulePlayer.h"
#include "ModuleBlocks.h"
#include "SDL/include/SDL.h"
#include <stdio.h>



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
			
			printf("Debug Mode ON\n");
		}
		else
		{
			GMODE = 0;
			DEBUG_MODE = 0;
			printf("Debug Mode Off \n");
			printf("God Mode Off \n");
		}
	}
	if (App->input->keys[SDL_SCANCODE_G] == Key_State::KEY_DOWN)
	{
		if (DEBUG_MODE == 1)
		{
			if (GMODE == 0)
			{
				GMODE = 1;
				printf("God Mode ON\n");
			}
			else
			{
				GMODE = 0;
				printf("God Mode Off\n");
			}
		}
		
		
	}
	
	if (DEBUG_MODE == 1)
	{
		if (GMODE)
		{
			if (App->input->keys[SDL_SCANCODE_LSHIFT] == Key_State::KEY_DOWN)
			{
				if (App->player->lifes != 2)
				{
					App->player->lifes++;
				}
				printf("%d", App->player->lifes);
			}


			if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_DOWN)
			{
				ascending = true;
			}
			if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_DOWN)
			{
				descending = true;
			}

			if (App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_DOWN)
			{
				printf("Choose level: ");

				scanf("%d", &levelChoose);

				switch (levelChoose)
				{
				case 0:
					App->fade->FadeToBlack((Module*)App->currentLevel, (Module*)App->sceneMenu, 90);
					break;

				case 1:
					App->fade->FadeToBlack((Module*)App->currentLevel, (Module*)App->sceneLevel_1, 90);
					break;

				case 2:
					App->fade->FadeToBlack((Module*)App->currentLevel, (Module*)App->sceneLevel_2, 90);
					break;

				case 3:
					App->fade->FadeToBlack((Module*)App->currentLevel, (Module*)App->sceneLevel_3, 90);
					break;

				case 4:
					App->fade->FadeToBlack((Module*)App->currentLevel, (Module*)App->sceneLevel_4, 90);
					break;

				case 5:
					App->fade->FadeToBlack((Module*)App->currentLevel, (Module*)App->sceneLevel_5, 90);
					break;

				case 6:
					App->fade->FadeToBlack((Module*)App->currentLevel, (Module*)App->sceneLevel_6, 90);
					break;

				case 7:
					App->fade->FadeToBlack((Module*)App->currentLevel, (Module*)App->sceneLevel_7, 90);
					break;

				case 8:
					App->fade->FadeToBlack((Module*)App->currentLevel, (Module*)App->sceneLevel_8, 90);
					break;

				case 9:
					App->fade->FadeToBlack((Module*)App->currentLevel, (Module*)App->sceneLevel_9, 90);
					break;

				case 10:
					App->fade->FadeToBlack((Module*)App->currentLevel, (Module*)App->sceneLevel_10, 90);
					break;

				case 11:
					App->fade->FadeToBlack((Module*)App->currentLevel, (Module*)App->sceneLevel_11, 90);
					break;

				case 12:
					App->fade->FadeToBlack((Module*)App->currentLevel, (Module*)App->sceneLevel_12, 90);
					break;

				case 13:
					App->fade->FadeToBlack((Module*)App->currentLevel, (Module*)App->sceneLevel_13, 90);
					break;

				case 14:
					App->fade->FadeToBlack((Module*)App->currentLevel, (Module*)App->sceneLevel_14, 90);
					break;

				case 15:
					App->fade->FadeToBlack((Module*)App->currentLevel, (Module*)App->sceneLevel_15, 90);
					break;

				case 16:
					App->fade->FadeToBlack((Module*)App->currentLevel, (Module*)App->sceneLevel_16, 90);
					break;


				default:
					break;
				}
			}
		}
		if (DEBUG_MODE == 1)
		{
			if (App->input->keys[SDL_SCANCODE_L] == Key_State::KEY_DOWN)
			{
				App->player->lifes = 0;
				App->player->instaloss = true;
			}
		}
	}

	
	
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleDebug::PostUpdate()
{
	return Update_Status::UPDATE_CONTINUE;
}

bool ModuleDebug::CleanUp()
{
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

void ModuleDebug::BlockOnMap(int x, int y)
{
	printf("%d \n", x);
	printf("%d \n", y);
	
	int gridposX =  ( x - 8 ) / 16;
	int gridposY =  (y - 32) / 16;
	App->blocks->AddBlock(Block_Type::NORMAL, gridposX, gridposY);
	printf("%d, %d \n", gridposX, gridposY);
	
}

void ModuleDebug::Disable()
{
	if (isEnabled)
	{
		isEnabled = false;
		CleanUp();
	}
}


