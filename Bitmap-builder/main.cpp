#pragma once

#include <iostream>
#include "Display.h"
#include <vector>
#include <Windows.h>
#include "BMP_Object.h"


int main(int argc, char * argv[]) {

	if (argc < 2) {
		std::cout << "Not enough arguments." << std::endl;
		return 0;
	}
	Display display;
	display.loadPicture(argv[1]);

	//Main loop flag
	bool quit = false;
	bool save = false;
	//Event handler
	SDL_Event e;
	//While application is running
	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			if (e.type == SDL_MOUSEBUTTONUP) {
				int x, y;
				SDL_GetMouseState(&x, &y);
				if (display.isSaveClicked(x, y))
				{
					std::cout << "Yay!! Button Clicked!\n";
					save = true; // This could be omitted, if the save function is run from here
					quit = true;
				}
			}
		}
	}
	BMP_Object loadedBmp; 
	loadedBmp.loadFile(argv[1]);
	loadedBmp.saveFile("test4.bmp");
	BMP_Object fromSDL = display.surfaceToBMP(argv[1]);
	fromSDL.saveFile("test3.bmp");
	return 0;
}