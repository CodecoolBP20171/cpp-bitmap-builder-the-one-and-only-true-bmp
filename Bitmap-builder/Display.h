#pragma once

#include <SDL.h>

class Display
{
public:
	Display();
	~Display();

	void loadPicture( char *);

private:

	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

	SDL_Window* gWindow = NULL;
	SDL_Surface* gScreenSurface = NULL;
	SDL_Surface* gImage = NULL;



};

