#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* path, SDL_Renderer* renderer) {
	SDL_Surface* surf = IMG_Load(path);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_FreeSurface(surf);

	return texture;
}