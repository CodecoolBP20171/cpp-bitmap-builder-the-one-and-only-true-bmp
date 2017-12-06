#pragma once

#include <iostream>
#include "Display.h"


int main(int argc, char * argv[]) {

	if (argc < 2) {
		std::cout << "Not enough arguments." << std::endl;
		return 0;
	}
	
	Display display;
	display.loadPicture(argv[1]);
	

	return 0;
}