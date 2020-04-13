#include "Animation.h"

Animation::Animation(SDL_Texture* _source, SDL_Rect* location, int rows, int columns, int _delay)
{
	source = _source;
	int frameWidth = location->w / columns;
	int frameHeight = location->h / rows;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			SDL_Rect frame;
			frame.x = location->x + j * frameWidth;
			frame.y = location->y - i * frameHeight;
			frame.w = frameWidth;
			frame.h = frameHeight;
			frames.push_back(frame);
		}
	}
	delay = _delay;
}

Animation::~Animation()
{
}

void Animation::step() {
	timer++;
	if (timer == delay) {
		timer = 0;
		currentFrame++;
		if (currentFrame == frames.size()) {
			currentFrame = 0;
		}
	}
}

SDL_Rect* Animation::getFrame() {
	return &frames[currentFrame];
}