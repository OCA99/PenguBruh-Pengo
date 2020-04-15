#include "WallVertical.h"

WallVertical::WallVertical() : GameObject::GameObject() {
	construct();
}

WallVertical::WallVertical(Vec2i _position) : GameObject::GameObject(_position) {
	construct();
}

WallVertical::~WallVertical() {

}

void WallVertical::update() {
	animation = animator->getCurrentValue();
}

void WallVertical::destroy() {
	// Define object destroy
}

void WallVertical::construct() {
	SDL_Texture* sprites = TextureManager::LoadTexture("assets/sprites/Stages.png");
	std::map<WallVerticalAnimations, Animation*>* states = new std::map<WallVerticalAnimations, Animation*>();
	SDL_Rect rect;
	rect.x = 216;
	rect.y = 0;
	rect.w = 8;
	rect.h = 256;
	Animation* normal = new Animation(sprites, &rect, 1, 1, 1, nullptr);
	(*states)[WallVerticalAnimations::Normal] = normal;
	rect.x = 456;
	rect.h = 16;
	Animation* shake = new Animation(sprites, &rect, 2, 1, 30, nullptr);
	(*states)[WallVerticalAnimations::Shake] = shake;
	animator = new StateMachine<WallVerticalAnimations, Animation*>(states);
	animator->setCurrentState(WallVerticalAnimations::Normal);
}