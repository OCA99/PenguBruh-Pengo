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
	GameObject::update();
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
	Animation* down = new Animation(sprites, &rect, 1, 2, 8, 1, nullptr);
	(*states)[PengoAnimations::WalkDown] = down;
	rect.x = 32;
	Animation* left = new Animation(sprites, &rect, 1, 2, 8, 1, nullptr);
	(*states)[PengoAnimations::WalkLeft] = left;
	rect.x = 64;
	Animation* up = new Animation(sprites, &rect, 1, 2, 8, 1, nullptr);
	(*states)[PengoAnimations::WalkUp] = up;
	rect.x = 96;
	Animation* right = new Animation(sprites, &rect, 1, 2, 8, 1, nullptr);
	(*states)[PengoAnimations::WalkRight] = right;
	rect.x = 0;
	rect.y = 32;
	Animation* die = new Animation(sprites, &rect, 1, 2, 8, 11, [] { std::cout << "You died" << std::endl; });
	(*states)[PengoAnimations::Die] = die;
	rect.y = 16;
	Animation* pushDown = new Animation(sprites, &rect, 1, 2, 10, 1, [&] { pushing = false; animator->getCurrentValue()->pause(); });
	(*states)[PengoAnimations::PushDown] = pushDown;
	rect.x = 32;
	Animation* pushLeft = new Animation(sprites, &rect, 1, 2, 10, 1, [&] { pushing = false; animator->getCurrentValue()->pause(); });
	(*states)[PengoAnimations::PushLeft] = pushLeft;
	rect.x = 64;
	Animation* pushUp = new Animation(sprites, &rect, 1, 2, 10, 1, [&] { pushing = false; animator->getCurrentValue()->pause(); });
	(*states)[PengoAnimations::PushUp] = pushUp;
	rect.x = 96;
	Animation* pushRight = new Animation(sprites, &rect, 1, 2, 10, 1, [&] { pushing = false; animator->getCurrentValue()->pause(); });
	(*states)[PengoAnimations::PushRight] = pushRight;
	animator = new StateMachine<PengoAnimations, Animation*>(states);
	animator->setCurrentState(PengoAnimations::WalkDown);
}