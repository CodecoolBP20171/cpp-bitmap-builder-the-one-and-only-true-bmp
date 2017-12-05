#include "BMP_Object.h"



BMP_Object::BMP_Object(long width, long height, WORD bitsPerPixel, std::vector<BYTE> pixelData) : width(width), 
	height(height), bitsPerPixel(bitsPerPixel), pixelData(pixelData) {} 

BMP_Object::~BMP_Object()
{
}

void BMP_Object::saveFile(const char * filename)
{
	unsigned long headersSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	unsigned long paddingSize = (4 - ((width * 3) % 4)) % 4;
	unsigned long pixelDataSize = height * ((width * (bitsPerPixel / 8)) + paddingSize);

	BITMAPINFOHEADER bmpInfoHeader = { 0 };

	// Set the size  
	bmpInfoHeader.biSize = sizeof(BITMAPINFOHEADER);

	// Bit count  
	bmpInfoHeader.biBitCount = bitsPerPixel;

	// Use all colors  
	bmpInfoHeader.biClrImportant = 0;

	// Use as many colors according to bits per pixel  
	bmpInfoHeader.biClrUsed = 0;

	// Store as un Compressed  
	bmpInfoHeader.biCompression = BI_RGB;

	// Set the height in pixels  
	bmpInfoHeader.biHeight = height;

	// Width of the Image in pixels  
	bmpInfoHeader.biWidth = width;

	// Default number of planes  
	bmpInfoHeader.biPlanes = 1;

	// Calculate the image size in bytes  
	bmpInfoHeader.biSizeImage = pixelDataSize;

	BITMAPFILEHEADER bfh = { 0 };

	// This value should be values of BM letters i.e 0x4D42  
	// 0x4D = M 0×42 = B storing in reverse order to match with endian  
	bfh.bfType = 0x4D42;
	//bfh.bfType = 'B'+('M' << 8); 

	// <<8 used to shift ‘M’ to end  */  

	// Offset to the RGBQUAD  
	bfh.bfOffBits = headersSize;

	// Total size of image including size of headers  
	bfh.bfSize = headersSize + pixelDataSize;

	// Create the file in disk to write  
	HANDLE hFile = CreateFile(filename,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	// Return if error opening file  
	if (!hFile) return;

	DWORD dwWritten = 0;

	// Write the File header  
	WriteFile(hFile,
		&bfh,
		sizeof(bfh),
		&dwWritten,
		NULL);

	// Write the bitmap info header  
	WriteFile(hFile,
		&bmpInfoHeader,
		sizeof(bmpInfoHeader),
		&dwWritten,
		NULL);

	// Write the RGB Data  
	WriteFile(hFile,
		pixelData.data(),
		bmpInfoHeader.biSizeImage,
		&dwWritten,
		NULL);

	// Close the file handle  
	CloseHandle(hFile);
}
