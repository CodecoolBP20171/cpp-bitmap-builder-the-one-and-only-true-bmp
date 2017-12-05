#pragma once

#include <vector>
#include <iostream>
#include <Windows.h>

class BMP_Object
{
public:
	BMP_Object(long width, long height, WORD bitsPerPixel, std::vector<BYTE> pixelData);
	~BMP_Object();
	void loadFile(const char* filename);
	void saveFile(const char* filename);

private:

	long width;
	long height;
	WORD bitsPerPixel;
	std::vector<BYTE> pixelData;
};