#include "Display.h"
#include <stdio.h>


Display::Display()
{	
	SCREEN_HEIGHT = 700;
	SCREEN_WIDTH = 1200;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		gWindow = SDL_CreateWindow("One and only BMP ", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			}
		else
		{	
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				}
				else
				{
					gScreenSurface = SDL_GetWindowSurface(gWindow);
				}
			}
		}
	}

	
}


Display::~Display()
{
	SDL_DestroyTexture(gTexture);
	gTexture = NULL;

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}


SDL_Texture* Display::loadTexture(char* path)
{
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path);
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
	}
	else
	{
		printf("Loaded pict(surface) height: %d , width %d", loadedSurface->h, loadedSurface->w);
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
		}
		SDL_FreeSurface(loadedSurface);
	}
	
	return newTexture;
}

bool Display::loadMedia(char * path)
{
	bool success = true;

	gTexture = loadTexture(path);
	if (gTexture == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}
	
	return success;
}

SDL_Rect Display::createRectangle() {
	SDL_Rect rectangle;

	int picWidth, picHeight;
	SDL_QueryTexture(gTexture, NULL, NULL, &picWidth, &picHeight);

	if (picWidth > 800 || picHeight > 600)
	{
		double ratio = picWidth / picHeight;
		if (ratio > 4 / 3) {
			picWidth = 800;
			picHeight = picWidth * ratio;
		}
		else {
			picHeight = 600;
			picWidth = picHeight * ratio;
		}
	}

	rectangle.x = 10;
	rectangle.y = 10;
	rectangle.h = picHeight;
	rectangle.w = picWidth;
	return rectangle;
}

void Display::loadPicture(char * filename) {

	SDL_RenderClear(gRenderer);
	Display::loadMedia(filename);
	
	SDL_Rect destRectangle = Display::createRectangle();

	SDL_RenderCopy(gRenderer, gTexture, NULL, & destRectangle );
	SDL_RenderPresent(gRenderer);

}
