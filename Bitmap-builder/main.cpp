#pragma once

#include <iostream>
#include "Display.h"
#include <vector>
#include <Windows.h>
#include "BMP_Object.h"
#include <string>
#include <cstring>


std::string createNewName(char* oldName) {
	std::string newName(oldName);
	std::cout << newName << "\n";
	newName.replace(newName.find(".") + 1, 3, "bmp");
	return newName;
}

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
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			if (e.type == SDL_MOUSEBUTTONUP) {
				int x, y;
				SDL_GetMouseState(&x, &y);
				if (display.isSaveClicked(x, y))
				{
					BMP_Object fromSDL = display.surfaceToBMP(argv[1]);
					fromSDL.saveFile(createNewName(argv[1]).c_str());
					save = true; // This could be omitted, if the save function is run from here
					quit = true;
				}
			}
		}
		if (save) {
			//loading both pictures
		}
	}
	BMP_Object loadedBmp; 
	loadedBmp.loadFile(argv[1]);
	loadedBmp.saveFile("test4.bmp");
	BMP_Object fromSDL = display.surfaceToBMP(argv[1]);
	fromSDL.saveFile("test3.bmp");
	return 0;
}