#include "grpch.h"

#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Platform/Opengl/stb_image.h"
namespace Gray
{
	
	Texture::Texture()
	{
		slot = -1;
		ID = 0;

		hasLoaded = false;
		isBound = false;
	}

	Texture::Texture(const std::string& path, int internalFormat, int externalFormat)
	{
		isBound = false;
		LoadTexture(path, internalFormat, externalFormat);
	}

	void Texture::LoadTexture(const std::string& path, int internalFormat, int externalFormat)
	{
		stbi_set_flip_vertically_on_load(true);

		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);


		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, nrChannels;
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, STBI_rgb_alpha);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, externalFormat, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			hasLoaded = true;
		}
		else
		{
			std::cout << "Error loading image";
			hasLoaded = false;
		}
		stbi_image_free(data);
	}

	void Texture::Bind(int slot)  const
	{
		if (hasLoaded && (!isBound || slot != this->slot))
		{
			this->slot = slot;

			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(GL_TEXTURE_2D, ID);
			isBound = true;
		}
	}

	void Texture::Unbind(int slot) const
	{
		if (hasLoaded && isBound)
		{
			this->slot = -1;

			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(GL_TEXTURE_2D, 0);
			isBound = false;
		}
	}

	int Texture::GetSlot() const
	{
		return slot;
	}
}