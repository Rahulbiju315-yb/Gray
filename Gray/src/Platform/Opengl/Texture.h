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
		Texture(const std::string& path, int internalFormat = GL_RGBA, int externalFormat = GL_RGBA);

		void Bind(int slot = 0) const;
		void Unbind(int slot = 0) const;
	};
}