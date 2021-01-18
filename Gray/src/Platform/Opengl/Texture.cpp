#include "grpch.h"

#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Platform/Opengl/stb_image.h"
namespace Gray
{
	std::unordered_map<int, uint> Texture::boundTexture_IDs;
	std::vector<Texture> unreferencedTextures;

	Texture::Texture() 
		: ID(0)
	{
	}


	void Texture::LoadTextureFrom(void* data, int width, int height, int internalFormat, int externalFormat)
	{
		CreateIfEmpty();
		Bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, externalFormat, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	bool Texture::LoadTexture(const std::string& path, bool flip, int internalFormat, int externalFormat)
	{
		CreateIfEmpty();
		Bind();

		stbi_set_flip_vertically_on_load(flip);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, nrChannels;
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, STBI_rgb_alpha);

		uint inf, exf;

		if (nrChannels == 3)
		{
			inf = GL_COMPRESSED_RGB;
			exf = GL_RGB;
		}
		else
		{
			inf = GL_COMPRESSED_RGBA;
			exf = GL_RGBA;
		}
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, externalFormat, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			GRAY_CORE_ERROR("Cannot load texture " + path);
			return false;
		}

		stbi_image_free(data);
		return true;
	}

	void Texture::LoadEmptyTexture(int width, int height, int internalFormat, int externalFormat)
	{
		CreateIfEmpty();
		Bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, externalFormat, GL_UNSIGNED_BYTE, nullptr);	
	}

	void Texture::LoadDepthTexture(int width, int height)
	{
		CreateIfEmpty();
		Bind();

		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, 
			GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, nullptr);

	}

	void Texture::LoadStencilTexture(int width, int height)
	{
		CreateIfEmpty();
		Bind();

		glBindTexture(GL_TEXTURE_2D, ID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_STENCIL_ATTACHMENT, width, height, 0, 
				GL_STENCIL_ATTACHMENT, GL_UNSIGNED_BYTE, nullptr);
	}

	void Texture::LoadDepthStencilTexture(int width, int height)
	{
		CreateIfEmpty();
		Bind();
		glBindTexture(GL_TEXTURE_2D, ID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, 
				GL_DEPTH24_STENCIL8, GL_UNSIGNED_BYTE, nullptr);
	}

	void Texture::Bind(int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, ID);
		boundTexture_IDs[slot] = ID;
	}

	void Texture::Unbind(int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, 0);
		boundTexture_IDs[slot] = 0;
	}

	bool Texture::IsBound() const
	{
		return boundTexture_IDs.find(ID) != boundTexture_IDs.end();
	}

	uint Texture::GetID() const
	{
		return ID;
	}

	void Texture::CopyFrom(const Texture& tex)
	{
		ID = tex.ID;
	}

	void Texture::CreateIfEmpty()
	{
		if(ID == 0)
			glGenTextures(1, &ID);
	}

	void Texture::Free()
	{
		glDeleteTextures(1, &ID);
	}
}