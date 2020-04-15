#include "TextureManager.h"

std::map<std::string, SDL_Texture*>* TextureManager::cache = new std::map<std::string, SDL_Texture*>();

SDL_Texture* TextureManager::LoadTexture(std::string path) {
	if ((*cache).find(path) != (*cache).end()) return (*cache)[path];
	std::ifstream fin(path);
	SDL_Surface* surf = IMG_Load(path.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surf);
	(*cache)[path] = texture;
	SDL_FreeSurface(surf);

	return texture;
}