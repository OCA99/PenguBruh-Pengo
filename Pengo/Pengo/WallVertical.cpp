#include "WallVertical.h"

WallVertical::WallVertical() : Wall::Wall() {
	construct();
}

WallVertical::WallVertical(Vec2i _position) : Wall::Wall(_position) {
	construct();
}

WallVertical::~WallVertical() {

}

void WallVertical::update() {
	animation = animator->getCurrentValue();
}

void WallVertical::construct() {
	SDL_Texture* sprites = TextureManager::LoadTexture("assets/sprites/Stages.png");
	std::map<WallAnimations, Animation*>* states = new std::map<WallAnimations, Animation*>();
	SDL_Rect rect;
	rect.x = 216;
	rect.y = 0;
	rect.w = 8;
	rect.h = 256;
	Animation* normal = new Animation(sprites, &rect, 1, 1, 1, 1, nullptr);
	(*states)[WallAnimations::Normal] = normal;
	rect.x = 684;
	rect.w = 16;
	Animation* shake = new Animation(sprites, &rect, 1, 2, 8, 1, nullptr);
	(*states)[WallAnimations::Shake] = shake;
	animator = new StateMachine<WallAnimations, Animation*>(states);
	animator->setCurrentState(WallAnimations::Normal);
}