#pragma once

namespace Gray
{
	struct Image
	{
		Image()
			: data(nullptr), path(""), width(0), height(0), nrChannels(0)
		{
			
		}

		~Image();

	    unsigned char* data;
		std::string path;
		int width;
		int height;
		int nrChannels;
	};
	
	void LoadImage(Image& image, bool flip=false);
	float GetR(const Image& image, int x, int y);
	float GetG(const Image& image, int x, int y);
	float GetB(const Image& image, int x, int y);
	
}