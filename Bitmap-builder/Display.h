#pragma once

#include <SDL.h>
#include <SDL_image.h>

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
	SDL_Renderer* gRenderer = NULL;
	SDL_Texture* gTexture = NULL;

	bool loadMedia(char*);
	SDL_Texture* loadTexture(char* );

};
