#include "WallHorizontal.h"

WallHorizontal::WallHorizontal() : Wall::Wall() {
	construct();
}

WallHorizontal::WallHorizontal(Vec2i _position) : Wall::Wall(_position) {
	construct();
}

WallHorizontal::~WallHorizontal() {

}

void WallHorizontal::update() {
	animation = animator->getCurrentValue();
}

void WallHorizontal::construct() {
	SDL_Texture* sprites = TextureManager::LoadTexture("assets/sprites/Stages.png");
	std::map<WallAnimations, Animation*>* states = new std::map<WallAnimations, Animation*>();
	SDL_Rect rect;
	rect.x = 228;
	rect.y = 260;
	rect.w = 224;
	rect.h = 8;
	Animation* normal = new Animation(sprites, &rect, 1, 1, 1, nullptr);
	(*states)[WallAnimations::Normal] = normal;
	rect.x = 456;
	rect.h = 16;
	Animation* shake = new Animation(sprites, &rect, 2, 1, 8, nullptr);
	(*states)[WallAnimations::Shake] = shake;
	animator = new StateMachine<WallAnimations, Animation*>(states);
	animator->setCurrentState(WallAnimations::Normal);
}