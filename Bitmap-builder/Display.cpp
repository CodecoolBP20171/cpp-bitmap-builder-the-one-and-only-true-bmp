#include "Display.h"
#include <stdio.h>




Display::Display()
{	
	SCREEN_HEIGHT = 700;
	SCREEN_WIDTH = 1200;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow("One and only BMP ", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}
}


Display::~Display()
{
	//Deallocate surface
	SDL_FreeSurface(gImage);
	gImage = NULL;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

void Display::loadPicture(char * filename) {
	gImage = SDL_LoadBMP(filename);
	if (gImage == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", filename, SDL_GetError());
	}
	else {
		//Apply the image
		SDL_BlitSurface(gImage, NULL, gScreenSurface, NULL);
		//Update the surface
		SDL_UpdateWindowSurface(gWindow);
	}
}
