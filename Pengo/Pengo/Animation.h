#pragma once

#include <SDL_image.h>
#include <vector>

class Animation
{
public:
	Animation(SDL_Texture* _source, SDL_Rect* location, int rows, int columns, int _delay);
	~Animation();
	void step();
	SDL_Rect* getFrame();
	SDL_Texture* source = nullptr;

private:
	int delay = 1;
	std::vector<SDL_Rect> frames;
	int currentFrame = 0;
	int timer = 0;

};