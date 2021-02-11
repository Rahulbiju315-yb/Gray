#pragma once

namespace Gray
{
	struct Image
	{
		Image();

	    std::unique_ptr<unsigned char> data;
		std::string path;
		int width;
		int height;
		int nrChannels;
	};
	
	void LoadImage(Image& image, const std::string& path, bool flip=false);
	float GetR(const Image& image, int x, int y);
	float GetG(const Image& image, int x, int y);
	float GetB(const Image& image, int x, int y);
	
}