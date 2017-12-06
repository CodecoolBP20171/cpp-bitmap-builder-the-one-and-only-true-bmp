#pragma once

#include <SDL.h>
#include <SDL_image.h>

class Display
{
public:
	Display();
	~Display();

	void loadPicture( char *);
	bool isSaveClicked(int &, int &);

private:

	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

	SDL_Window* gWindow = NULL;
	SDL_Surface* gScreenSurface = NULL;
	SDL_Surface* gImage = NULL;
	SDL_Renderer* gRenderer = NULL;
	SDL_Texture* gTexture = NULL;
	SDL_Rect buttonRect;

	bool loadMedia(char*);
	SDL_Texture* loadTexture(char* );
	SDL_Rect createRectangle();
	

};

