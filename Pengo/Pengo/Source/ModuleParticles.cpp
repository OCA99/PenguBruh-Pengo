#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ACTIVE_STARS; ++i)
		particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	texture = App->textures->Load("assets/sprites/Miscellaneous.png");

	score100.anim.GenerateAnimation({ 3, 111, 13, 8 }, 1, 1);
	score100.lifetime = 60;

	score400.anim.GenerateAnimation({ 19, 111, 15, 8 }, 1, 1);
	score400.lifetime = 60;

	score1600.anim.GenerateAnimation({ 36, 111, 16, 8 }, 1, 1);
	score1600.lifetime = 60;

	score3200.anim.GenerateAnimation({ 54, 111, 16, 8 }, 1, 1);
	score3200.lifetime = 60;

	score6400.anim.GenerateAnimation({ 72, 111, 16, 8 }, 1, 1);
	score6400.lifetime = 60;

	return true;
}

Update_Status ModuleParticles::PreUpdate()
{
	for (uint i = 0; i < MAX_ACTIVE_STARS; ++i)
	{
		if (particles[i] != nullptr && particles[i]->pendingToDelete)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	for(uint i = 0; i < MAX_ACTIVE_STARS; ++i)
	{
		if(particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

Update_Status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_STARS; ++i)
	{
		Particle* particle = particles[i];

		if(particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if(particle->Update() == false)
		{
			particles[i]->SetToDelete();
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleParticles::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_STARS; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			App->render->Blit(texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Particle* ModuleParticles::AddParticle(const Particle& particle, int x, int y)
{
	Particle* newParticle = nullptr;

	for (uint i = 0; i < MAX_ACTIVE_STARS; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			newParticle = new Particle(particle);
			newParticle->frameCount = 0;			// We start the frameCount as the negative delay
			newParticle->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			newParticle->position.y = y;

			particles[i] = newParticle;
			break;
		}
	}

	return newParticle;
}