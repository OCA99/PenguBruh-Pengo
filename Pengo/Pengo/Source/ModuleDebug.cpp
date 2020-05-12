#include "Module.h"
#include "ModuleDebug.h"
#include "ModuleInput.h"
#include "Application.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
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


