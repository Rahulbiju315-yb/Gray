#pragma once

#include "NoCopy.h"
#include "Shared.h"
#include "WeakRef.h"
#include "Gray/Image/Image.h"

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
		void LoadTextureFrom(const Image& image);
		bool LoadTexture(const std::string& path, bool flip, int internalFormat = GL_RGBA, int externalFormat = GL_RGBA);
		void LoadEmptyTexture(int width, int height, int internalFormat = GL_RGBA, int externalFormat = GL_RGBA);
		void LoadDepthTexture(int width, int height);
		void LoadStencilTexture(int width, int height);
		void LoadDepthStencilTexture(int width, int height);
		void Bind(int slot = 0) const;
		void Unbind(int slot = 0) const;

		uint GetID() const;
		
	private:
		static std::unordered_map<int, uint> boundTexture_IDs;
		uint ID;

		Texture();

		Texture(const Texture&) = default;
		Texture(Texture&&) = default;

		Texture& operator=(const Texture&) = default;
		Texture& operator=(Texture&&)  = default;

		void CopyFrom(const Texture& tex);
		void Free();

		friend class Shared<Texture>;
		friend class NoCopy<Texture>;
		friend class WeakRef<Texture>;

	};

	WeakRef<Texture> EmptyTex();

}