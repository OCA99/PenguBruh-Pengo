#pragma once

#include <SDL_image.h>
#include <iostream>
#include <fstream>
#include "Game.h"

class TextureManager {
public:
	static SDL_Texture* LoadTexture(const char* path);
};