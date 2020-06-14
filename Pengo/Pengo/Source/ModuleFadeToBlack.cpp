#include "ModuleFadeToBlack.h"

#include "Application.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

#include "SDL/include/SDL_render.h"

ModuleFadeToBlack::ModuleFadeToBlack(bool startEnabled) : Module(startEnabled)
{
	screenRect = {0, 0, SCREEN_WIDTH * SCREEN_SIZE, SCREEN_HEIGHT * SCREEN_SIZE};
	firstScreenRect = { 0, 0, SCREEN_WIDTH * SCREEN_SIZE, SCREEN_HEIGHT * SCREEN_SIZE };
}

ModuleFadeToBlack::~ModuleFadeToBlack()
{

}

bool ModuleFadeToBlack::Start()
{
	LOG("Preparing Fade Screen");

	// Enable blending mode for transparency
	SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);
	return true;
}

Update_Status ModuleFadeToBlack::Update()
{
	// Exit this function if we are not performing a fade
	if (currentStep == Fade_Step::NONE) return Update_Status::UPDATE_CONTINUE;

	if (currentStep == Fade_Step::TO_BLACK)
	{
		++frameCount;
		if (frameCount > maxFadeFrames)
		{
			fadePause = 0;
			if (!App->player->stayInLevel)
			{
				moduleToDisable->Disable();
				moduleToEnable->Enable();
			}

			currentStep = Fade_Step::FROM_BLACK;
		}
	}
	else
	{
		if (App->player->stayInLevel)
		{
			if (fadePause != 30) fadePause++;

			if (fadePause == 30)
			{
				--frameCount;
				if (frameCount <= 0)
				{
					currentStep = Fade_Step::NONE;
				}
			}
		} else{
			--frameCount;
			if (frameCount <= 0)
			{
				currentStep = Fade_Step::NONE;
			}
		}
		
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleFadeToBlack::PostUpdate()
{
	// Exit this function if we are not performing a fade
	if (currentStep == Fade_Step::NONE) return Update_Status::UPDATE_CONTINUE;

	float fadeRatio = (float)frameCount / ((float)maxFadeFrames);

	// Render the black square with alpha on the screen
	SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, (Uint8)(255.0f));
	screenRect.h = firstScreenRect.h * fadeRatio;
	SDL_RenderFillRect(App->render->renderer, &screenRect);


	return Update_Status::UPDATE_CONTINUE;
}

bool ModuleFadeToBlack::FadeToBlack(Module* moduleToDisable, Module* moduleToEnable, float frames)
{
	bool ret = false;

	// If we are already in a fade process, ignore this call
	if(currentStep == Fade_Step::NONE)
	{
		currentStep = Fade_Step::TO_BLACK;
		frameCount = 0;
		maxFadeFrames = 45;

		this->moduleToDisable = moduleToDisable;
		this->moduleToEnable = moduleToEnable;

		ret = true;
	}

	return ret;
}