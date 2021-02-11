#pragma once

#include "Platform/Opengl/Texture.h"
#include "thread"
#include "mutex"
#include "Gray/Image/Image.h"
#include "Gray/DS/SafeQueue.h"
#include "TextureLoader.h"

namespace Gray
{
	class TextureManager
	{
	public:
		TextureManager();
		~TextureManager();

		WeakRef<Texture> GetTexture(const std::string& path);
		//bool HasLoaded(const std::string& path);
		
		bool RequireLoading();
		bool RequireInit();

		void InitTextures();
	private:


		std::vector<NoCopy<Texture>> textures;
		std::vector<std::string> paths;
		uint nUninit;

		SafeQueue< std::pair<WeakRef<Texture>, std::string> > toLoad;
		SafeQueue< std::pair<WeakRef<Texture>, Image> > toInit;

		friend class TextureLoader;
		TextureLoader& tl;
	};
}