#pragma once

#include <string>
#include <GL/glew.h>

namespace Gray
{
	class Texture
	{
	private:
		unsigned int ID;

	public:
		Texture(const std::string& path, int internalFormat = GL_RGBA8, int externalFormat = GL_RGBA);

		void bind(int slot = 0) const;
		void unbind(int slot = 0) const;
	};
}