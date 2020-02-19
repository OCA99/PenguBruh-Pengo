#include "SDL/include/SDL.h"
#pragma comment(lib, "SDL/lib/x86/SDL2.lib")
#pragma comment(lib, "SDL/lib/x86/SDL2main.lib")

#include <string>

int main(int argc, char* argv[]) {

	SDL_Init(SDL_INIT_EVERYTHING);
	std::string name = "window";
	SDL_Window* window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0); //SDL_WINDOW_FULLSCREEN);

	return 0;
}