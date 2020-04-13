#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* path) {
	std::ifstream fin(path);
	if (fin.is_open()) {
		std::cout << "file open" << std::endl;
	}
	else {
		std::cout << "file not open" << std::endl;
	}

	if (fin.fail()) {
		std::cout << "file open failed" << std::endl;
	}
	else {
		std::cout << "file open success" << std::endl;
	}
	SDL_Surface* surf = IMG_Load(path);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surf);
	SDL_FreeSurface(surf);

	return texture;
}