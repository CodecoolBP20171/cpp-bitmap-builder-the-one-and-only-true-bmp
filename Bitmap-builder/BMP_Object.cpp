#include "BMP_Object.h"



BMP_Object::BMP_Object()
{
}

BMP_Object::BMP_Object(long width, long height, WORD bitsPerPixel, std::vector<BYTE> pixelData) : width(width),
	height(height), bitsPerPixel(bitsPerPixel), pixelData(pixelData) {} 

BMP_Object::~BMP_Object()
{
}

void BMP_Object::setWidth(long newWidth)
{
	width = newWidth;
}

void BMP_Object::setHeight(long newHeight)
{
	height = newHeight;
}

void BMP_Object::setPixelData(std::vector<BYTE> newPixelData)
{
	pixelData = newPixelData;
}

void BMP_Object::setBitsPerPixel(WORD newBitsPerPixel)
{
	bitsPerPixel = newBitsPerPixel;
}

void BMP_Object::loadFile(const char * filename)
{
	//BMP_Object loadedBmp;
	BITMAPFILEHEADER bmpheader;
	BITMAPINFOHEADER bmpinfo;
	// value to be used in ReadFile funcs
	DWORD bytesread;
	// open file to read from
	HANDLE file = CreateFile(filename,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_SEQUENTIAL_SCAN,
		NULL);
	if (NULL == file)
	{
		std::cout << "cannot open file" << std::endl;
	}
	if (ReadFile(file, &bmpheader, sizeof(BITMAPFILEHEADER), &bytesread, NULL) == false)
	{
		std::cout << "cannot read file header data" << std::endl;
		CloseHandle(file);
	}

	// Read bitmap info
	if (ReadFile(file, &bmpinfo, sizeof(BITMAPINFOHEADER), &bytesread, NULL) == false)
	{
		std::cout << "cannot read bmp info header data" << std::endl;
		CloseHandle(file);
	}

	// check if file is actually a bmp
	if (bmpheader.bfType != 'MB')
	{
		std::cout << "loaded file is not a bitmap image" << std::endl;
		CloseHandle(file);
	}

	// get image measurements
	width = bmpinfo.biWidth;
	height = abs(bmpinfo.biHeight);
	bitsPerPixel = bmpinfo.biBitCount;

	// Check if bmp is uncompressed
	if (bmpinfo.biCompression != BI_RGB)
	{
		std::cout << "bmp is compressed" << std::endl;
		CloseHandle(file);
	}

	// Check if we have 24 bit bmp
	if (bmpinfo.biBitCount != 24)
	{
		std::cout << "bmp is not 24 bit image" << std::endl;
		CloseHandle(file);
	}

	// create buffer to hold the data
	unsigned long size = bmpheader.bfSize - bmpheader.bfOffBits;
	BYTE* Buffer = new BYTE[size];
	// move file pointer to start of bitmap data
	SetFilePointer(file, bmpheader.bfOffBits, NULL, FILE_BEGIN);
	// read bmp data
	if (ReadFile(file, Buffer, size, &bytesread, NULL) == false)
	{
		delete[] Buffer;
		CloseHandle(file);
	}

	std::vector<BYTE> pixelData;
	for (size_t i = 0; i < size; i++)
	{
		pixelData.push_back(Buffer[i]);
	}
	// everything successful here: close file and return buffer

	CloseHandle(file);
	
	setPixelData(pixelData);

}

void BMP_Object::saveFile(const char * filename)
{
	unsigned long headersSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	//unsigned long paddingSize = (4 - ((width * 3) % 4)) % 4;
	unsigned long pixelDataSize = height * ((width * (bitsPerPixel / 8))); // +paddingSize);

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

std::vector<BYTE> BMP_Object::getPixelData()
{
	return pixelData;
}

long BMP_Object::getWidth()
{
	return width;
}

long BMP_Object::getHeight()
{
	return height;
}

WORD BMP_Object::getBitsPerPixel()
{
	return bitsPerPixel;
}
