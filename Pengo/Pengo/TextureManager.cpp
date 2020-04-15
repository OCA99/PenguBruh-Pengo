#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* path) {
	std::ifstream fin(path);
	SDL_Surface* surf = IMG_Load(path);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surf);
	SDL_FreeSurface(surf);

	return texture;
}