#pragma once

#include <string>
#include <GL/glew.h>

namespace Gray
{

	enum class TextureType
	{
		NullTexture, // Implies texture hasnt been loaded yet
		ImageTexture, 
		EmptyTexture,
		StencilTexture,
		DepthTexture,
		DepthStencilTexture
	};

	class Texture
	{
	public:
		Texture();
		Texture(TextureType type,int width, int height, int internalFormat = GL_RGBA, int externalFormat = GL_RGBA);
		Texture(const std::string& path, int internalFormat = GL_RGBA, int externalFormat = GL_RGBA);
		Texture(const Texture& tex);
		Texture(Texture&& tex) noexcept;

		~Texture();

		//Texture& operator=(const Texture& tex) = delete;
		//Texture& operator=(Texture&& tex) = delete;

		void LoadTexture(const std::string& path, int internalFormat = GL_RGBA, int externalFormat = GL_RGBA);
		void LoadEmptyTexture(int width, int height, int internalFormat = GL_RGBA, int externalFormat = GL_RGBA);
		void LoadDepthTexture(int width, int height);
		void LoadStencilTexture(int width, int height);
		void LoadDepthStencilTexture(int width, int height);

		void Bind(int slot = 0) const;
		void Unbind(int slot = 0) const;

		int GetSlot() const;
		uint GetID() const;

	private:
		static std::unordered_map<int, uint> boundTexture_IDs;

		uint ID;
		TextureType type;
		mutable int slot;
		int* refCount;

		mutable bool isBound;
		bool hasLoaded;

	};

}