#include "Block.h"

Block::Block() : GameObject::GameObject() {
	construct();
}

Block::Block(Vec2i _position) : GameObject::GameObject(_position) {
	construct();
}

Block::~Block() {

}

void Block::update() {
	animation = animator->getCurrentValue();
}

void Block::destroy() {
	// Define object destroy
}

void Block::construct() {
	SDL_Texture* sprites = TextureManager::LoadTexture("assets/sprites/Stages.png");
	std::map<BlockAnimations, Animation*>* states = new std::map<BlockAnimations, Animation*>();
	SDL_Rect rect;
	rect.x = 708;
	rect.y = 0;
	rect.w = 16;
	rect.h = 16;
	Animation* normal = new Animation(sprites, &rect, 1, 1, 1, nullptr);
	(*states)[BlockAnimations::Normal] = normal;
	rect.y = 48;
	rect.w = 144;
	Animation* breaking = new Animation(sprites, &rect, 1, 9, 8, [&] { destroy(); });
	(*states)[BlockAnimations::Breaking] = breaking;
	animator = new StateMachine<BlockAnimations, Animation*>(states);
	animator->setCurrentState(BlockAnimations::Normal);
	type = 2;
}