#include "grpch.h"
#include "Image.h"
#include "Platform/Opengl/stb_image.h"

Gray::Image::~Image()
{
	if (data)
		stbi_image_free(data);
}

void Gray::LoadImage(const std::string& path, Image& image)
{
	image.data = stbi_load(path.c_str(), &image.width, &image.height, &image.nrChannels, 0);

	if (image.data)
		GRAY_WARN("Succussfuly loaded image " + path);

	else
		GRAY_WARN("Failed to load image " + path); //Gokul made this (stupid buggy) program!!!!(jk)

}

float Gray::GetR(const Image& image, uint x, uint y)
{
	assert(image.data);
	assert(x <= image.width);
	assert(y <= image.height);
	
	int offset = (y * image.width + x) * image.nrChannels;
	unsigned char red = image.data[offset];

	return (float)red / 255;
}

float Gray::GetG(const Image& image, uint x, uint y)
{
	assert(image.data);
	assert(x <= image.width);
	assert(y <= image.height);

	int offset = (y * image.width + x) * image.nrChannels;
	unsigned char green = image.data[offset + 1];

	return (float)green / 255;
}

float Gray::GetB(const Image& image, uint x, uint y)
{
	assert(image.data);
	assert(x <= image.width);
	assert(y <= image.height);

	int offset = (y * image.width + x) * image.nrChannels;
	unsigned char blue = image.data[offset + 2];

	return (float)blue / 255;
}


