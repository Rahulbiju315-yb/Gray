#include "grpch.h"

#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Platform/Opengl/stb_image.h"
namespace Gray
{
	std::unordered_map<int, uint> Texture::boundTexture_IDs;
	std::vector<Texture> unreferencedTextures;

	Texture::Texture() 
		: slot(-1), ID(0), hasLoaded(false), isBound(false)
	{
	}

	void Texture::LoadTexture(const std::string& path, int internalFormat, int externalFormat)
	{
		CreateIfEmpty();
		Bind();

		stbi_set_flip_vertically_on_load(true);
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
		}
		else
		{
			GRAY_CORE_ERROR("Cannot load texture " + path);
		}
		stbi_image_free(data);		
	}

	void Texture::LoadEmptyTexture(int width, int height, int internalFormat, int externalFormat)
	{
		CreateIfEmpty();
		Bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
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

		hasLoaded = true;
	}

	void Texture::Bind(int slot) const
	{
		this->slot = slot;

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
		return boundTexture_IDs[slot] == ID;
	}

	int Texture::GetSlot() const
	{
		return slot;
	}

	uint Texture::GetID() const
	{
		return ID;
	}

	void Texture::CopyFrom(const Texture& tex)
	{
		ID = tex.ID;
		slot = tex.slot;

		isBound = tex.isBound;
		hasLoaded = tex.hasLoaded;
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