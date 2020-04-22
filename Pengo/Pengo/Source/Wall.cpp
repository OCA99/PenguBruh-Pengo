#include "Wall.h"

#include "Application.h"
//#include "ModuleCollisions.h"
//#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"

Wall::Wall(int x, int y) : position(x, y)
{
	position.x = x;
	position.y = y;
}

Wall::~Wall()
{

}

void Wall::Update()
{
	if (currentAnim != nullptr)
		currentAnim->Update();

	if (currentAnim == &shakeAnim) {
		shakeCounter++;
		if (shakeCounter == shakeTime) {
			currentAnim = &normalAnim;
		}
	}
}

void Wall::Draw()
{
	if (currentAnim != nullptr)
	{
		SDL_Rect r = currentAnim->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
	}
}

void Wall::Shake() {
	currentAnim = &shakeAnim;
	shakeCounter = 0;
}
