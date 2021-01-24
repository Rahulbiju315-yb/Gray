#pragma once

namespace Gray
{
	struct Image
	{
		~Image();

	    unsigned char* data;
		std::string path;
		int width;
		int height;
		int nrChannels;
	};
	
	void LoadImage(const std::string& path, Image& image);
	float GetR(const Image& image, uint x, uint y);
	float GetG(const Image& image, uint x, uint y);
	float GetB(const Image& image, uint x, uint y);
	
}