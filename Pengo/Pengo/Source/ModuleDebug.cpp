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
			level += 1;
			LevelUpDown();
		}
		if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_DOWN)
		{
			level -= 1;
			LevelUpDown();
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
	
	switch (level)
	{
		case 1:
			App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneLevel_2, 90);
			printf("Lvl1");
			break;
		case 2:
			App->fade->FadeToBlack((Module*)App->sceneLevel_2, (Module*)App->sceneLevel_3, 90);
			printf("Lvl2");
			break;
		case 3:
			App->fade->FadeToBlack((Module*)App->sceneLevel_3, (Module*)App->sceneLevel_4, 90);
			printf("Lvl3");
			break;
		case 4:
			App->fade->FadeToBlack((Module*)App->sceneLevel_4, (Module*)App->sceneLevel_5, 90);
			printf("Lvl4");
			break;
		case 5:
			App->fade->FadeToBlack((Module*)App->sceneLevel_5, (Module*)App->sceneLevel_6, 90);
			printf("Lvl5");
			break;
		case 6:
			App->fade->FadeToBlack((Module*)App->sceneLevel_6, (Module*)App->sceneLevel_7, 90);
			printf("Lvl6");
			break;
		case 7:
			App->fade->FadeToBlack((Module*)App->sceneLevel_7, (Module*)App->sceneLevel_8, 90);
			printf("Lvl7");
			break;
		case 8:
			App->fade->FadeToBlack((Module*)App->sceneLevel_8, (Module*)App->sceneLevel_9, 90);
			printf("Lvl8");
			break;
		case 9:
			App->fade->FadeToBlack((Module*)App->sceneLevel_9, (Module*)App->sceneLevel_10, 90);
			printf("Lvl9");
			break;
		case 10:
			App->fade->FadeToBlack((Module*)App->sceneLevel_10, (Module*)App->sceneLevel_11, 90);
			printf("Lvl10");
			break;
		case 11:
			App->fade->FadeToBlack((Module*)App->sceneLevel_11, (Module*)App->sceneLevel_12, 90);
			printf("Lvl11");
			break;
		case 12:
			App->fade->FadeToBlack((Module*)App->sceneLevel_12, (Module*)App->sceneLevel_13, 90);
			printf("Lvl12");
			break;
		case 13:
			App->fade->FadeToBlack((Module*)App->sceneLevel_13, (Module*)App->sceneLevel_14, 90);
			printf("Lvl13");
			break;
	}
	


}
