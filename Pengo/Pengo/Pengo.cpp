#include "Pengo.h"

Pengo::Pengo() : GameObject::GameObject() {
	construct();
}

Pengo::Pengo(Vec2i _position) : GameObject::GameObject(_position) {
	construct();
}

Pengo::~Pengo() {

}

void Pengo::update() {
	animation = animator->getCurrentValue();
}

void Pengo::construct() {
	SDL_Texture* sprites = TextureManager::LoadTexture("assets/sprites/pengos.png");
	std::map<PengoAnimations, Animation*>* states = new std::map<PengoAnimations, Animation*>();
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = 32;
	rect.h = 16;
	Animation* down = new Animation(sprites, &rect, 1, 2, 15, nullptr);
	(*states)[PengoAnimations::WalkDown] = down;
	rect.x = 32;
	Animation* left = new Animation(sprites, &rect, 1, 2, 15, nullptr);
	(*states)[PengoAnimations::WalkLeft] = left;
	rect.x = 64;
	Animation* up = new Animation(sprites, &rect, 1, 2, 15, nullptr);
	(*states)[PengoAnimations::WalkUp] = up;
	rect.x = 96;
	Animation* right = new Animation(sprites, &rect, 1, 2, 15, nullptr);
	(*states)[PengoAnimations::WalkRight] = right;
	animator = new StateMachine<PengoAnimations, Animation*>(states);
	animator->setCurrentState(PengoAnimations::WalkDown);
}