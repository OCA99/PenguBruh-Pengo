#pragma once

#include <SDL_image.h>
#include <vector>
#include <functional>

class Animation
{
public:
	Animation(SDL_Texture* _source, SDL_Rect* location, int rows, int columns, int _delay, std::function<void()> _callback);
	~Animation();
	void step();
	SDL_Rect* getFrame();
	SDL_Texture* source = nullptr;
	void play();
	void pause();

private:
	int delay = 1;
	std::vector<SDL_Rect> frames;
	int currentFrame = 0;
	int timer = 0;
	bool running = true;
	std::function<void()> callback;
};