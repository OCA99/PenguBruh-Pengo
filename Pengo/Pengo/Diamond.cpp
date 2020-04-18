#include "Diamond.h"

Diamond::Diamond() : GameObject::GameObject() {
	construct();
}

Diamond::Diamond(Vec2i _position) : GameObject::GameObject(_position) {
	construct();
}

Diamond::~Diamond() {

}

void Diamond::update() {
	animation = animator->getCurrentValue();
}

void Diamond::destroy() {
	// Define object destroy
}

void Diamond::construct() {
	SDL_Texture* sprites = TextureManager::LoadTexture("assets/sprites/Stages.png");
	std::map<DiamondAnimations, Animation*>* states = new std::map<DiamondAnimations, Animation*>();
	SDL_Rect rect;
	rect.x = 708;
	rect.y = 16;
	rect.w = 16;
	rect.h = 16;
	Animation* normal = new Animation(sprites, &rect, 1, 1, 1, 1, nullptr);
	(*states)[DiamondAnimations::Normal] = normal;
	animator = new StateMachine<DiamondAnimations, Animation*>(states);
	animator->setCurrentState(DiamondAnimations::Normal);
	type = 3;
}