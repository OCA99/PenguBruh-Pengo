#include "Pengo.h"

Pengo::Pengo() {
	SDL_Texture* pengo = TextureManager::LoadTexture("assets/sprites/pengos.png");
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = 32;
	rect.h = 16;
	animation = new Animation(pengo, &rect, 1, 2, 15);
	gridPosition = Vec2i(0, 0);
	position = Vec2f(0, 0);
}

Pengo::~Pengo() {

}