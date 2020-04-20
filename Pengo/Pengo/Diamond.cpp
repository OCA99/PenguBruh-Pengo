#include "Diamond.h"

Diamond::Diamond() : Block::Block() {
	construct();
}

Diamond::Diamond(Vec2i _position) : Block::Block(_position) {
	construct();
}

Diamond::~Diamond() {

}

void Diamond::update() {
	Block::update();
}

void Diamond::clean() {
	Block::clean();
}

void Diamond::construct() {
	SDL_Texture* sprites = TextureManager::LoadTexture("assets/sprites/Stages.png");
	std::map<BlockAnimations, Animation*>* states = new std::map<BlockAnimations, Animation*>();
	SDL_Rect rect;
	rect.x = 708;
	rect.y = 16;
	rect.w = 16;
	rect.h = 16;
	Animation* normal = new Animation(sprites, &rect, 1, 1, 1, 1, nullptr);
	(*states)[BlockAnimations::Normal] = normal;
	rect.x = 0;
	rect.y = 256;
	Animation* empty = new Animation(sprites, &rect, 1, 1, 1, 1, nullptr);
	(*states)[BlockAnimations::Empty] = empty;
	animator = new StateMachine<BlockAnimations, Animation*>(states);
	animator->setCurrentState(BlockAnimations::Normal);
	type = 3;
	speed = 2;
}