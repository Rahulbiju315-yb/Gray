#include "grpch.h"
#include "Texture.h"

namespace Gray
{

	Texture::Texture() 
		: ID(0)
	{
		glGenTextures(1, &ID);
	}


	void Texture::LoadTextureFrom(const Image& image)
	{
		assert(image.data);
		Bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		uint inf, exf;

		exf = GL_RGBA;

		if (image.nrChannels == 3)
		{
			inf = GL_RGB;
		}
		else
		{
			inf = GL_RGBA;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, inf, image.width, image.height, 0, exf, GL_UNSIGNED_BYTE, image.data.get());
		glGenerateMipmap(GL_TEXTURE_2D);
		
	}

	bool Texture::LoadTexture(const std::string& path, bool flip, int internalFormat, int externalFormat)
	{
		Bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		Image image;
		LoadImage(image, path, flip);

		if (image.data)
		{
			LoadTextureFrom(image);
		}
		else
		{
			GRAY_CORE_ERROR("Cannot load texture " + path);
			return false;
		}

		return true;
	}

	void Texture::LoadEmptyTexture(int width, int height, int internalFormat, int externalFormat)
	{
		Bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, externalFormat, GL_UNSIGNED_BYTE, nullptr);	
	}

	void Texture::LoadDepthTexture(int width, int height)
	{
		Bind();

		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, 
			GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, nullptr);

	}

	void Texture::LoadStencilTexture(int width, int height)
	{
		Bind();

		glBindTexture(GL_TEXTURE_2D, ID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_STENCIL_ATTACHMENT, width, height, 0, 
				GL_STENCIL_ATTACHMENT, GL_UNSIGNED_BYTE, nullptr);
	}

	void Texture::LoadDepthStencilTexture(int width, int height)
	{
		Bind();
		glBindTexture(GL_TEXTURE_2D, ID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, 
				GL_DEPTH24_STENCIL8, GL_UNSIGNED_BYTE, nullptr);
	}


	void Texture::Bind(int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, ID);
	}

	void Texture::Unbind(int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	uint Texture::GetID() const
	{
		return ID;
	}

	void Texture::CopyFrom(const Texture& tex)
	{
		ID = tex.ID;
	}

	void Texture::Free()
	{
		glDeleteTextures(1, &ID);
	}

	WeakRef<Texture> EmptyTex()
	{
		static bool init = false;
		static NoCopy<Texture> tex;

		if (!init)
		{
			tex->LoadEmptyTexture(1, 1);
			init = true;
		}

		return WeakRef<Texture>(tex);
	}
}