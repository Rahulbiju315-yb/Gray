#include "grpch.h"
#include "Image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Platform/Opengl/stb_image.h"

Gray::Image::~Image()
{
	if (data)
		stbi_image_free(data);
}

void Gray::LoadImage(Image& image, bool flip)
{
	stbi_set_flip_vertically_on_load(flip);
	image.data = stbi_load(image.path.c_str(), &image.width, &image.height, &image.nrChannels, STBI_rgb_alpha);

	if (image.data)
	{
		GRAY_WARN("Succussfuly loaded image " + image.path);
	}
	else
		GRAY_WARN("Failed to load image " + image.path);

}

float Gray::GetR(const Image& image, int x, int y)
{
	assert(image.data);
	assert(x <= image.width);
	assert(y <= image.height);
	assert(x >= 0);
	assert(y >= 0);

	int offset = (y * image.width + x) * image.nrChannels;
	unsigned char red = image.data[offset];

	return (float)red / 255;
}

float Gray::GetG(const Image& image, int x, int y)
{
	assert(image.data);
	assert(x <= image.width);
	assert(y <= image.height);
	assert(x >= 0);
	assert(y >= 0);

	int offset = (y * image.width + x) * image.nrChannels;
	unsigned char green = image.data[offset + 1];

	return (float)green / 255;
}

float Gray::GetB(const Image& image, int x, int y)
{
	assert(image.data);
	assert(x >= 0);
	assert(y >= 0);
	assert(x <= image.width);
	assert(y <= image.height);

	int offset = (y * image.width + x) * image.nrChannels;
	unsigned char blue = image.data[offset + 2];

	return (float)blue / 255;
}


