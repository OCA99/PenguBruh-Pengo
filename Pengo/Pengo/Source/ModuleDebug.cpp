#include "Module.h"
#include "ModuleDebug.h"
#include "ModuleInput.h"
#include "Application.h"
#include "ModuleFadeToBlack.h"
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

	if (App->input->keys[SDL_SCANCODE_G] == Key_State::KEY_DOWN)
	{
		if (GMODE == 0)
		{
			GMODE = 1;
			printf("God Mode ON");
		}
		else
		{
			GMODE = 0;
			printf("God Mode Off");
		}
	}
	if (GMODE == 1)
	{
		
		if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_DOWN)
		{
			if (level < 15)
			{
				descending = false;
				level += 1;
				LevelUpDown();
			}
			
		}
		if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_DOWN)
		{
			if (level > 0)
			{
				descending = true;
				level -= 1;
				LevelUpDown();
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

void ModuleDebug::Disable()
{
	if (isEnabled)
	{
		isEnabled = false;
		CleanUp();
	}
}

void ModuleDebug::LevelUpDown()
{
	printf("%d", level);
	printf("%d", descending);

	
	switch (level)
	{
		case 1:
			if (!descending)
			{
				App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneLevel_2, 20);
			}
			else
			{
				App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneMenu, 20);
			}
			printf("Lvl1");
			break;
		case 2:
			if (!descending)
			{
				App->fade->FadeToBlack((Module*)App->sceneLevel_2, (Module*)App->sceneLevel_3, 20);
			}
			else
			{
				App->fade->FadeToBlack((Module*)App->sceneLevel_2, (Module*)App->sceneLevel_1, 20);
			}
			printf("Lvl2");
			break;
		case 3:
			if (!descending)
			{
				App->fade->FadeToBlack((Module*)App->sceneLevel_3, (Module*)App->sceneLevel_4, 20);
			}
			else
			{
				App->fade->FadeToBlack((Module*)App->sceneLevel_3, (Module*)App->sceneLevel_2, 20);
			}
			printf("Lvl3");
			break;
		case 4:
			if (!descending)
			{
				App->fade->FadeToBlack((Module*)App->sceneLevel_4, (Module*)App->sceneLevel_5, 20);
			}
			else
			{
				App->fade->FadeToBlack((Module*)App->sceneLevel_4, (Module*)App->sceneLevel_3, 20);
			}
			printf("Lvl4");
			break;
		case 5:
			if (!descending)
			{
				App->fade->FadeToBlack((Module*)App->sceneLevel_5, (Module*)App->sceneLevel_6, 20);
			}
			else
			{
				App->fade->FadeToBlack((Module*)App->sceneLevel_5, (Module*)App->sceneLevel_4, 20);
			}
			printf("Lvl5");
			break;
		case 6:
			if (!descending)
			{
				App->fade->FadeToBlack((Module*)App->sceneLevel_6, (Module*)App->sceneLevel_7, 20);
			}
			else
			{
				App->fade->FadeToBlack((Module*)App->sceneLevel_6, (Module*)App->sceneLevel_5, 20);
			}
			printf("Lvl6");
			break;
		case 7:
			if (!descending)
			{
				App->fade->FadeToBlack((Module*)App->sceneLevel_7, (Module*)App->sceneLevel_8, 20);
			}
			else
			{
				App->fade->FadeToBlack((Module*)App->sceneLevel_7, (Module*)App->sceneLevel_6, 20);
			}
			printf("Lvl7");
			break;
		case 8:
			if (!descending)
			{
				App->fade->FadeToBlack((Module*)App->sceneLevel_8, (Module*)App->sceneLevel_9, 20);
			}
			else
			{
				App->fade->FadeToBlack((Module*)App->sceneLevel_8, (Module*)App->sceneLevel_7, 20);
			}
			printf("Lvl8");
			break;
		case 9:
			if (!descending)
			{
				App->fade->FadeToBlack((Module*)App->sceneLevel_9, (Module*)App->sceneLevel_10, 20);
			}
			else
			{
				App->fade->FadeToBlack((Module*)App->sceneLevel_9, (Module*)App->sceneLevel_8, 20);
			}
			printf("Lvl9");
			break;
		case 10:
			if (!descending)
			{
				App->fade->FadeToBlack((Module*)App->sceneLevel_10, (Module*)App->sceneLevel_11, 20);
			}
			else
			{
				App->fade->FadeToBlack((Module*)App->sceneLevel_10, (Module*)App->sceneLevel_9, 20);
			}
			printf("Lvl10");
			break;
		case 11:
			if (!descending)
			{
				App->fade->FadeToBlack((Module*)App->sceneLevel_11, (Module*)App->sceneLevel_12, 20);
			}
			else
			{
				App->fade->FadeToBlack((Module*)App->sceneLevel_12, (Module*)App->sceneLevel_10, 20);
			}
			printf("Lvl11");
			break;
		case 12:
			if (!descending)
			{
				App->fade->FadeToBlack((Module*)App->sceneLevel_12, (Module*)App->sceneLevel_13, 20);
			}
			else
			{
				App->fade->FadeToBlack((Module*)App->sceneLevel_12, (Module*)App->sceneLevel_11, 20);
			}
			printf("Lvl12");
			break;
		case 13:
			if (!descending)
			{
				App->fade->FadeToBlack((Module*)App->sceneLevel_13, (Module*)App->sceneLevel_14, 20);
			}
			else
			{
				App->fade->FadeToBlack((Module*)App->sceneLevel_13, (Module*)App->sceneLevel_12, 20);
			}
			printf("Lvl13");
			break;
		case 14:
			if (!descending) 
			{
				App->fade->FadeToBlack((Module*)App->sceneLevel_14, (Module*)App->sceneMenu, 20);
			}
			else
			{
				App->fade->FadeToBlack((Module*)App->sceneLevel_14, (Module*)App->sceneLevel_13, 20);
			}
			
			printf("Lvl14");
			break;
	}
	
	
	/*
	if (!descending)
	{
		App->fade->FadeToBlack((Module*)(12+level), (Module*)(12+level+1), 20);
	}
	else
	{
		App->fade->FadeToBlack((Module*)(12+level), (Module*)(12+level-1), 20);
	}
	*/
			
	

}
