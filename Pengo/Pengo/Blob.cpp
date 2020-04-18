#include "Blob.h"

Blob::Blob() : GameObject::GameObject() {
	construct();
}

Blob::Blob(Vec2i _position) : GameObject::GameObject(_position) {
	construct();
}

Blob::~Blob() {

}

void Blob::update() {
	animation = animator->getCurrentValue();
}

void Blob::construct() {
	SDL_Texture* sprites = TextureManager::LoadTexture("assets/sprites/pengos.png");
	std::map<BlobAnimations, Animation*>* states = new std::map<BlobAnimations, Animation*>();
	SDL_Rect rect;
	rect.x = 128;
	rect.y = 128;
	rect.w = 96;
	rect.h = 16;
	Animation* spawn = new Animation(sprites, &rect, 1, 6, 15, 1, [&] { (*animator).setCurrentState(BlobAnimations::WalkDown); });
	(*states)[BlobAnimations::Spawn] = spawn;
	rect.y = 144;
	rect.w = 32;
	Animation* down = new Animation(sprites, &rect, 1, 2, 15, 1, nullptr);
	(*states)[BlobAnimations::WalkDown] = down;
	rect.x = 160;
	Animation* left = new Animation(sprites, &rect, 1, 2, 15, 1, nullptr);
	(*states)[BlobAnimations::WalkLeft] = left;
	rect.x = 176;
	Animation* up = new Animation(sprites, &rect, 1, 2, 15, 1, nullptr);
	(*states)[BlobAnimations::WalkUp] = up;
	rect.x = 192;
	Animation* right = new Animation(sprites, &rect, 1, 2, 15, 1, nullptr);
	(*states)[BlobAnimations::WalkRight] = right;
	animator = new StateMachine<BlobAnimations, Animation*>(states);
	animator->setCurrentState(BlobAnimations::Spawn);
	type = 4;
}