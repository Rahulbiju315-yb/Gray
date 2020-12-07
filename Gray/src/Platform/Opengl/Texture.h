#pragma once

#include <string>
#include <GL/glew.h>

namespace Gray
{
	class Texture
	{
	private:
		unsigned int ID;
		
		mutable int slot;
		mutable bool isBound;

		bool hasLoaded;

	public:
		Texture();
		Texture(const std::string& path, int internalFormat = GL_RGBA, int externalFormat = GL_RGBA);
		
		void LoadTexture(const std::string& path, int internalFormat = GL_RGBA, int externalFormat = GL_RGBA);
		void Bind(int slot = 0) const;
		void Unbind(int slot = 0) const;

		int GetSlot() const;
	};
}