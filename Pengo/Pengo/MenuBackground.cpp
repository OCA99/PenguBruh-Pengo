#include "MenuBackground.h"

MenuBackground::MenuBackground() : GameObject::GameObject()
{
	construct();
}

MenuBackground::MenuBackground(Vec2i _position) : GameObject::GameObject(_position)

{
	construct();
}

void MenuBackground::update() {
	GameObject::update();
	animation = animator->getCurrentValue();
}

MenuBackground::~MenuBackground()
{
}

void MenuBackground::construct() {
	SDL_Texture* sprites = TextureManager::LoadTexture("assets/sprites/menusprites.png");
	std::map<MenuBackgroundAnimations, Animation*>* states = new std::map<MenuBackgroundAnimations, Animation*>();
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = 224;
	rect.h = 288;
	Animation* normal = new Animation(sprites, &rect, 1, 1, 1, 180, [&] { Game::changeScene("level_1"); });
	(*states)[MenuBackgroundAnimations::Normal] = normal;
	animator = new StateMachine<MenuBackgroundAnimations, Animation*>(states);
	animator->setCurrentState(MenuBackgroundAnimations::Normal);
}