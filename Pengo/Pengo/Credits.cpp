#include "Credits.h"

Credits::Credits() : GameObject::GameObject()
{
	construct();
}

Credits::Credits(Vec2i _position) : GameObject::GameObject(_position)

{
	construct();
}

void Credits::update() {
	GameObject::update();
	animation = animator->getCurrentValue();
}

Credits::~Credits()
{
}

void Credits::construct() {
	SDL_Texture* sprites = TextureManager::LoadTexture("assets/sprites/credits.png");
	std::map<CreditsAnimations, Animation*>* states = new std::map<CreditsAnimations, Animation*>();
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = 224;
	rect.h = 288;
	Animation* normal = new Animation(sprites, &rect, 1, 1, 1, 240, [&] { Game::changeScene("menu"); });
	(*states)[CreditsAnimations::Normal] = normal;
	animator = new StateMachine<CreditsAnimations, Animation*>(states);
	animator->setCurrentState(CreditsAnimations::Normal);
}