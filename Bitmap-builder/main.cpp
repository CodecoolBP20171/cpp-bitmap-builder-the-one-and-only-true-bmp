#pragma once

#include <iostream>
#include "Display.h"
#include <vector>
#include <Windows.h>
#include "BMP_Object.h"


int main(int argc, char * argv[]) {

	if (argc < 2) {
		std::cout << "Not enough arguments." << std::endl;
		//return 0;
	}
	Display display;
	display.loadPicture(argv[1]);

	// Testing BMP writing from hardcoded data
	std::vector<BYTE> pixelData;
	for (size_t i = 0; i < 255 ; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			pixelData.push_back(i);
		}
	}
	BMP_Object bmp(12, 12, 24, pixelData);
	bmp.saveFile("test.bmp");

	BMP_Object fromSDL = display.surfaceToBMP(argv[1]);
	fromSDL.saveFile("test3.bmp");
	
	return 0;
}