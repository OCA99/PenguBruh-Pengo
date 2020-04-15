#pragma once

#include <SDL_image.h>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "Game.h"

class TextureManager {
public:
	static SDL_Texture* LoadTexture(std::string path);

private:
	static std::map<std::string, SDL_Texture*>* cache;
};