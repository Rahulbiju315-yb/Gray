#pragma once

#include <string>
#include <GL/glew.h>

namespace Gray
{
	class Texture
	{
	private:
		unsigned int ID;
		int slot;

		bool hasLoaded;
		bool isBound;

	public:
		Texture();
		Texture(const std::string& path, int internalFormat = GL_RGBA, int externalFormat = GL_RGBA);
		
		void LoadTexture(const std::string& path, int internalFormat = GL_RGBA, int externalFormat = GL_RGBA);
		void Bind(int slot = 0) ;
		void Unbind(int slot = 0) ;

		int GetSlot();
	};
}