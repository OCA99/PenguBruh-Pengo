#include "WallHorizontal.h"

WallHorizontal::WallHorizontal() : GameObject::GameObject() {
	construct();
}

WallHorizontal::WallHorizontal(Vec2i _position) : GameObject::GameObject(_position) {
	construct();
}

WallHorizontal::~WallHorizontal() {

}

void WallHorizontal::update() {
	animation = animator->getCurrentValue();
}

void WallHorizontal::destroy() {
	// Define object destroy
}

void WallHorizontal::construct() {
	SDL_Texture* sprites = TextureManager::LoadTexture("assets/sprites/Stages.png");
	std::map<WallHorizontalAnimations, Animation*>* states = new std::map<WallHorizontalAnimations, Animation*>();
	SDL_Rect rect;
	rect.x = 228;
	rect.y = 260;
	rect.w = 224;
	rect.h = 8;
	Animation* normal = new Animation(sprites, &rect, 1, 1, 1, nullptr);
	(*states)[WallHorizontalAnimations::Normal] = normal;
	rect.x = 456;
	rect.h = 16;
	Animation* shake = new Animation(sprites, &rect, 2, 1, 30, nullptr);
	(*states)[WallHorizontalAnimations::Shake] = shake;
	animator = new StateMachine<WallHorizontalAnimations, Animation*>(states);
	animator->setCurrentState(WallHorizontalAnimations::Normal);
}