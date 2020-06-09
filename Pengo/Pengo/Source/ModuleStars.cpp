#include "ModuleStars.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"

#include "SDL/include/SDL_timer.h"

ModuleStars::ModuleStars(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_ACTIVE_STARS; ++i)
		stars[i] = nullptr;
}

ModuleStars::~ModuleStars()
{

}

bool ModuleStars::Start()
{
	LOG("Loading particles");
	texture = App->textures->Load("assets/sprites/stages.png");

	int count = 0;

	for (int i = 0; i < 28; i++) {
		AddStar(i * 8, 24, count % 16);
		count++;
	}

	for (int i = 0; i < 30; i++) {
		AddStar(216, 32 + i * 8, count % 16);
		count++;
	}

	for (int i = 0; i < 28; i++) {
		AddStar(216 - i * 8, 272, count % 16);
		count++;
	}

	for (int i = 0; i < 30; i++) {
		AddStar(0, 264 - i * 8, count % 16);
		count++;
	}

	return true;
}

Update_Status ModuleStars::PreUpdate()
{
	for (uint i = 0; i < MAX_ACTIVE_STARS; ++i)
	{
		if (stars[i] != nullptr && stars[i]->pendingToDelete)
		{
			delete stars[i];
			stars[i] = nullptr;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

bool ModuleStars::CleanUp()
{

	for (uint i = 0; i < MAX_ACTIVE_STARS; ++i)
	{
		if (stars[i] != nullptr)
		{
			delete stars[i];
			stars[i] = nullptr;
		}
	}

	return true;
}

Update_Status ModuleStars::Update()
{
	if (!starsActive) return Update_Status::UPDATE_CONTINUE;

	for (uint i = 0; i < MAX_ACTIVE_STARS; ++i)
	{
		Star* star = stars[i];

		if (star == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if (star->Update() == false)
		{
			star->SetToDelete();
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

#include <iostream>

Update_Status ModuleStars::PostUpdate()
{
	if (!starsActive) return Update_Status::UPDATE_CONTINUE;

	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_STARS; ++i)
	{
		Star* star = stars[i];

		if (star != nullptr)
		{
			App->render->Blit(texture, star->position.x, star->position.y, &(star->anim.GetCurrentFrame()));
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

void ModuleStars::AddStar(int x, int y, int startPos)
{
	Star* star = nullptr;

	for (uint i = 0; i < MAX_ACTIVE_STARS; ++i)
	{
		//Finding an empty slot for a new particle
		if (stars[i] == nullptr)
		{
			star = new Star(startPos);
			star->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			star->position.y = y;

			stars[i] = star;
			break;
		}
	}
}