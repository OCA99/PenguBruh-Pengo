#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
//#include "ModuleParticles.h"
#include "ModuleAudio.h"
//#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleBlocks.h"
#include "ModuleEnemies.h"
#include "ModuleWalls.h"
#include "ModuleFonts.h"

#include <stdio.h>

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	// idle animation - just one sprite
	idleAnim.GenerateAnimation({ 0, 0, 16, 16 }, 1, 1);

	// move upwards
	walkUpAnim.GenerateAnimation({ 64, 0, 32, 16 }, 1, 2);
	walkUpAnim.loop = true;
	walkUpAnim.speed = 0.1f;

	walkDownAnim.GenerateAnimation({ 0, 0, 32, 16 }, 1, 2);
	walkDownAnim.loop = true;
	walkDownAnim.speed = 0.1f;

	walkLeftAnim.GenerateAnimation({ 32, 0, 32, 16 }, 1, 2);
	walkLeftAnim.loop = true;
	walkLeftAnim.speed = 0.1f;

	walkRightAnim.GenerateAnimation({ 96, 0, 32, 16 }, 1, 2);
	walkRightAnim.loop = true;
	walkRightAnim.speed = 0.1f;

	pushUpAnim.GenerateAnimation({ 64, 16, 32, 16 }, 1, 2);
	pushUpAnim.loop = false;
	pushUpAnim.speed = 0.1f;

	pushDownAnim.GenerateAnimation({ 0, 16, 32, 16 }, 1, 2);
	pushDownAnim.loop = false;
	pushDownAnim.speed = 0.1f;

	pushLeftAnim.GenerateAnimation({ 32, 16, 32, 16 }, 1, 2);
	pushLeftAnim.loop = false;
	pushLeftAnim.speed = 0.1f;

	pushRightAnim.GenerateAnimation({ 96, 16, 32, 16 }, 1, 2);
	pushRightAnim.loop = false;
	pushRightAnim.speed = 0.1f;

	dieAnim.GenerateAnimation({ 0, 32, 32, 16 }, 1, 2);
	dieAnim.loop = true;
	dieAnim.speed = 0.1f;

	direction = Directions::Down;
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("assets/sprites/pengos.png");
	currentAnimation = &idleAnim;

	//laserFx = App->audio->LoadFx("Assets/Fx/laser.wav");
	//explosionFx = App->audio->LoadFx("Assets/Fx/explosion.wav");

	gridPosition.x = 6;
	gridPosition.y = 6;

	targetPosition.x = gridPosition.x * 16 + 8;
	targetPosition.y = gridPosition.y * 16 + 32;

	position.x = gridPosition.x * 16 + 8;
	position.y = gridPosition.y * 16 + 32;

	destroyed = false;

	//collider = App->collisions->AddCollider({ position.x, position.y, 32, 16 }, Collider::Type::PLAYER, this);

	// TODO 0: Notice how a font is loaded and the meaning of all its arguments 
	//char lookupTable[] = { "!  ,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz" };
	//scoreFont = App->fonts->Load("Assets/Fonts/rtype_font.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 1);

	// TODO 4: Try loading "rtype_font3.png" that has two rows to test if all calculations are correct
	//char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	//scoreFont = App->fonts->Load("Assets/Fonts/rtype_font3.png", lookupTable, 2);

	return ret;
}

Update_Status ModulePlayer::Update()
{
	int x = 0;
	int y = 0;
	
	positionToGrid(position.x, position.y, x, y);
	if (App->enemies->EnemyInGridPosition(x, y)) {
		dead = true;
		currentAnimation = &dieAnim;
	}
	if (App->enemies->EnemyInGridPosition(x, y)) App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneMenu, 90);
	// Moving the player with the camera scroll
	//App->player->position.x += 1;

		if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
		{
			lastPressed = (int)SDL_SCANCODE_A;
		}
		else if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_UP) {
			lastPressed = (int)SDL_SCANCODE_0;
		}

		if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
		{
			lastPressed = (int)SDL_SCANCODE_D;
		}
		else if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_UP) {
			lastPressed = (int)SDL_SCANCODE_0;
		}

		if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT)
		{
			lastPressed = (int)SDL_SCANCODE_S;
		}
		else if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_UP) {
			lastPressed = (int)SDL_SCANCODE_0;
		}

		if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT)
		{
			lastPressed = (int)SDL_SCANCODE_W;
		}
		else if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_UP) {
			lastPressed = (int)SDL_SCANCODE_0;
		}

		if (!dead) {
			switch (lastPressed) {
			case (int)SDL_SCANCODE_A:
				if (!moving) {
					currentAnimation->running = true;
					if (currentAnimation != &walkLeftAnim)
					{
						walkLeftAnim.Reset();
						currentAnimation = &walkLeftAnim;
					}
					direction = Directions::Left;
					if (!App->blocks->BlockInGridPosition(gridPosition.x - 1, gridPosition.y)) {
						gridPosition.x -= 1;
					}
				}
				break;
			case (int)SDL_SCANCODE_D:
				if (!moving) {
					currentAnimation->running = true;
					if (currentAnimation != &walkRightAnim)
					{
						walkRightAnim.Reset();
						currentAnimation = &walkRightAnim;
					}
					direction = Directions::Right;
					if (!App->blocks->BlockInGridPosition(gridPosition.x + 1, gridPosition.y)) {
						gridPosition.x += 1;
					}
				}
				break;
			case (int)SDL_SCANCODE_S:
				if (!moving) {
					currentAnimation->running = true;
					if (currentAnimation != &walkDownAnim)
					{
						walkDownAnim.Reset();
						currentAnimation = &walkDownAnim;
					}
					direction = Directions::Down;
					if (!App->blocks->BlockInGridPosition(gridPosition.x, gridPosition.y + 1)) {
						gridPosition.y += 1;
					}
				}
				break;
			case (int)SDL_SCANCODE_W:
				if (!moving) {
					currentAnimation->running = true;
					if (currentAnimation != &walkUpAnim)
					{
						walkUpAnim.Reset();
						currentAnimation = &walkUpAnim;
					}
					direction = Directions::Up;
					if (!App->blocks->BlockInGridPosition(gridPosition.x, gridPosition.y - 1)) {
						gridPosition.y -= 1;
					}
				}
				break;
			default:
				break;
			}
		}

	if (gridPosition.x < 0) gridPosition.x = 0;
	if (gridPosition.x > 12) gridPosition.x = 12;
	if (gridPosition.y < 0) gridPosition.y = 0;
	if (gridPosition.y > 14) gridPosition.y = 14;

	targetPosition.x = gridPosition.x * 16 + 8;
	targetPosition.y = gridPosition.y * 16 + 32;

	if (position.x < targetPosition.x) {
		position.x += speed;
	}
	else if (position.x > targetPosition.x) {
		position.x -= speed;
	}

	if (position.y < targetPosition.y) {
		position.y += speed;
	}
	else if (position.y > targetPosition.y) {
		position.y -= speed;
	}

	if (position.x == targetPosition.x && position.y == targetPosition.y) {
		moving = false;
	}
	else {
		moving = true;
	}

	if (!moving && currentAnimation != &pushUpAnim && currentAnimation != &pushDownAnim && currentAnimation != &pushLeftAnim && currentAnimation != &pushRightAnim) {
		currentAnimation->running = false;
	}

	if (!dead)
	{
		if (!moving && App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN) {
			switch (direction) {
			case Directions::Up:
				if (!App->blocks->PositionInMap(gridPosition.x, gridPosition.y - 1)) App->walls->PushWall(0);
				App->blocks->PushBlock(gridPosition.x, gridPosition.y, gridPosition.x, gridPosition.y - 1);
				pushUpAnim.Reset();
				currentAnimation = &pushUpAnim;
				break;
			case Directions::Down:
				if (!App->blocks->PositionInMap(gridPosition.x, gridPosition.y + 1)) App->walls->PushWall(1);
				App->blocks->PushBlock(gridPosition.x, gridPosition.y, gridPosition.x, gridPosition.y + 1);
				pushDownAnim.Reset();
				currentAnimation = &pushDownAnim;
				break;
			case Directions::Left:
				if (!App->blocks->PositionInMap(gridPosition.x - 1, gridPosition.y)) App->walls->PushWall(2);
				App->blocks->PushBlock(gridPosition.x, gridPosition.y, gridPosition.x - 1, gridPosition.y);
				pushLeftAnim.Reset();
				currentAnimation = &pushLeftAnim;
				break;
			case Directions::Right:
				if (!App->blocks->PositionInMap(gridPosition.x + 1, gridPosition.y)) App->walls->PushWall(3);
				App->blocks->PushBlock(gridPosition.x, gridPosition.y, gridPosition.x + 1, gridPosition.y);
				pushRightAnim.Reset();
				currentAnimation = &pushRightAnim;
				break;
			default:
				break;
			}
		}
	}
	if (currentAnimation == &pushUpAnim && currentAnimation->HasFinished()) {
		currentAnimation = &walkUpAnim;
	}
	if (currentAnimation == &pushDownAnim && currentAnimation->HasFinished()) {
		currentAnimation = &walkDownAnim;
	}
	if (currentAnimation == &pushLeftAnim && currentAnimation->HasFinished()) {
		currentAnimation = &walkLeftAnim;
	}
	if (currentAnimation == &pushRightAnim && currentAnimation->HasFinished()) {
		currentAnimation = &walkRightAnim;
	}

	currentAnimation->Update();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate()
{

	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}

	/*// Draw UI (score) --------------------------------------
	sprintf_s(scoreText, 10, "%7d", score);

	// TODO 3: Blit the text of the score in at the bottom of the screen
	App->fonts->BlitText(58, 248, scoreFont, scoreText);

	App->fonts->BlitText(150, 248, scoreFont, "this is just a font test");
	*/
	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::positionToGrid(int gx, int gy, int& x, int& y) {
	x = (gx - 8) / 16;
	y = (gy - 32) / 16;
}