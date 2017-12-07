#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "BMP_Object.h"
#include <deque>

class Display
{
public:
	Display();
	~Display();

	void loadPicture( const char *);
	void loadPicture(const char *, const char *);

	bool isSaveClicked(int &, int &);
	BMP_Object surfaceToBMP( char * );

private:
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

	SDL_Window* gWindow = NULL;
	SDL_Surface* gScreenSurface = NULL;
	SDL_Surface* gImage = NULL;
	SDL_Renderer* gRenderer = NULL;
	SDL_Texture* gTexture = NULL;
	SDL_Point centerLeft;
	SDL_Point centerRight;
	SDL_Rect buttonRect;

	bool loadMedia(const char*);
	SDL_Texture* loadTexture(const char* );
	SDL_Rect createRectangle(std::string);
	

};

