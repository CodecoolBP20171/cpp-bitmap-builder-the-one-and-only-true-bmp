#pragma once
#include <SDL.h>
#include <iostream>


int main(int argc, char * argv[]) {
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		std::cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
	}
	else {
		std::cout << "SDL initialization succeeded!";
	}
	std::cin.get();
	return 0;
}