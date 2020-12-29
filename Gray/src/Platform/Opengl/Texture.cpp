#include "grpch.h"

#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Platform/Opengl/stb_image.h"
namespace Gray
{
	std::unordered_map<int, uint> Texture::boundTexture_IDs;
	std::vector<Texture> unreferncedTextures;

	Texture::Texture() 
		: slot(-1), ID(0), hasLoaded(false), isBound(false), type(TextureType::NullTexture), refCount(nullptr)
	{
		//refernce counter
		refCount = new int;
		*refCount = 1;
	}

	Texture::Texture(TextureType type, int width, int height, int internalFormat, int externalFormat) 
		: slot(-1), ID(0), hasLoaded(false), isBound(false), refCount(nullptr)
	{
		//Load texture and initialise texture type
		if (type == TextureType::EmptyTexture)
			LoadEmptyTexture(width, height, internalFormat, externalFormat);

		else if (type == TextureType::DepthTexture)
			LoadDepthTexture(width, height);

		else if (type == TextureType::StencilTexture)
			LoadStencilTexture(width, height);

		else if (type == TextureType::DepthStencilTexture)
			LoadDepthStencilTexture(width, height);

		else
		{
			// Defaulting to ExmptyTexture when type is NullTexture or ImageTexture
			LoadEmptyTexture(width, height);
			GRAY_ERROR("Illegal TextureType passed to Texture Constructor. Defaulting to EmptyTexture");
		}

		//refernce counter
		refCount = new int;
		*refCount = 0;
	}

	Texture::Texture(const std::string& path, int internalFormat, int externalFormat) 
		: ID(0), isBound(false), hasLoaded(false)
	{
		LoadTexture(path, internalFormat, externalFormat);
	}

	Texture::Texture(const Texture& tex)
		: ID(tex.ID), type(tex.type), slot(tex.slot), 
		refCount(tex.refCount), isBound(tex.isBound), hasLoaded(tex.hasLoaded)
	{
		(*refCount)++;
	}

	Texture::Texture(Texture&& tex) noexcept
		: ID(tex.ID),
		type(tex.type),
		slot(tex.slot),
		isBound(tex.isBound),
		hasLoaded(tex.hasLoaded),
		refCount(std::move(tex.refCount))
	{
		(*refCount)++;
	}

	Texture::~Texture()
	{
		if (ID != 0 && *refCount == 1)
		{
			if (boundTexture_IDs[slot] == ID) // unrefereced bound textures are moved to a vector for further management
			{
				GRAY_WARN("Bound texture going out of scope !!!");
				GRAY_WARN("ID = " + std::to_string(ID) + " slot = " + std::to_string(slot));
				GRAY_WARN("Texture will be moved to std::vector<Texture> unreferencedTexture");

				unreferncedTextures.push_back(std::move(*this));
			}

			glDeleteTextures(1, &ID);
			delete refCount;
		}
		else
		{
			(*refCount)--;
		}
	}


	void Texture::LoadTexture(const std::string& path, int internalFormat, int externalFormat)
	{
		if (!hasLoaded) // A texture can be initialised only once. this check is done for all load methods
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
				GRAY_CORE_ERROR("Cannot load texture " + path);
				hasLoaded = false;
			}
			stbi_image_free(data);
			type = TextureType::ImageTexture;
		}
	}

	void Texture::LoadEmptyTexture(int width, int height, int internalFormat, int externalFormat)
	{
		if (!hasLoaded)
		{
			glGenTextures(1, &ID);
			glBindTexture(GL_TEXTURE_2D, ID);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, externalFormat, GL_UNSIGNED_BYTE, nullptr);
			hasLoaded = true;
			type = TextureType::EmptyTexture;
		}
	}

	void Texture::LoadDepthTexture(int width, int height)
	{
		if (!hasLoaded) 
		{
			glGenTextures(1, &ID);
			glBindTexture(GL_TEXTURE_2D, ID);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, 
				GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, nullptr);

			hasLoaded = true;
			type = TextureType::DepthTexture;
		}
	}

	void Texture::LoadStencilTexture(int width, int height)
	{
		if (!hasLoaded) 
		{
			glGenTextures(1, &ID);
			glBindTexture(GL_TEXTURE_2D, ID);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_STENCIL_ATTACHMENT, width, height, 0, 
				 GL_STENCIL_ATTACHMENT, GL_UNSIGNED_BYTE, nullptr);

			hasLoaded = true;
			type = TextureType::StencilTexture;
		}
	}

	void Texture::LoadDepthStencilTexture(int width, int height)
	{
		if (!hasLoaded)
		{
			glGenTextures(1, &ID);
			glBindTexture(GL_TEXTURE_2D, ID);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, 
				 GL_DEPTH24_STENCIL8, GL_UNSIGNED_BYTE, nullptr);

			hasLoaded = true;
			type = TextureType::DepthStencilTexture;
		}
	}

	void Texture::Bind(int slot)  const
	{
		// Bind a texture only when it has been loaded and is not already bound to the slot
		if (hasLoaded && (!(boundTexture_IDs[slot] == ID)|| slot != this->slot)) 
		{
			this->slot = slot;

			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(GL_TEXTURE_2D, ID);
			boundTexture_IDs[slot] = ID;
		}
	}

	void Texture::Unbind(int slot) const
	{
		//Only a loaded and bound (to the part. slot) texture can be unbound
		if (hasLoaded && (boundTexture_IDs[slot] == ID))
		{
			this->slot = -1;

			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(GL_TEXTURE_2D, 0);
			boundTexture_IDs[slot] = 0;
		}
	}

	int Texture::GetSlot() const
	{
		return slot;
	}
	uint Texture::GetID() const
	{
		return ID;
	}
}