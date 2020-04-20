#include "NormalBlock.h"

NormalBlock::NormalBlock() : Block::Block() {
	construct();
}

NormalBlock::NormalBlock(Vec2i _position) : Block::Block(_position) {
	construct();
}

NormalBlock::~NormalBlock() {
	//std::cout << "normal block destructor" << std::endl;
}

void NormalBlock::update() {
	Block::update();
}

void NormalBlock::clean() {
	Block::clean();
	//delete this;
}

void NormalBlock::construct() {
	SDL_Texture* sprites = TextureManager::LoadTexture("assets/sprites/Stages.png");
	std::map<BlockAnimations, Animation*>* states = new std::map<BlockAnimations, Animation*>();
	SDL_Rect rect;
	rect.x = 708;
	rect.y = 0;
	rect.w = 16;
	rect.h = 16;
	Animation* normal = new Animation(sprites, &rect, 1, 1, 1, 1, nullptr);
	(*states)[BlockAnimations::Normal] = normal;
	rect.y = 48;
	rect.w = 144;
	Animation* breaking = new Animation(sprites, &rect, 1, 9, 8, 1, [&] { clean(); });
	(*states)[BlockAnimations::Breaking] = breaking;
	rect.x = 0;
	rect.y = 256;
	rect.w = 16;
	Animation* empty = new Animation(sprites, &rect, 1, 1, 1, 1, nullptr);
	(*states)[BlockAnimations::Empty] = empty;
	animator = new StateMachine<BlockAnimations, Animation*>(states);
	animator->setCurrentState(BlockAnimations::Normal);
	type = 2;
	speed = 2;
}