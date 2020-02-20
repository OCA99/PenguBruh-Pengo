#include "SDL/include/SDL.h"
#pragma comment(lib, "SDL/lib/x86/SDL2.lib")
#pragma comment(lib, "SDL/lib/x86/SDL2main.lib")

#include <string>

int main(int argc, char* argv[]) {

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN); //SDL_WINDOW_FULLSCREEN);

	SDL_Delay(5000);

	return 0;
}