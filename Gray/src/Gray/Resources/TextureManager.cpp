#include "grpch.h"
#include "TextureManager.h"
#include "TextureLoaderPool.h"

namespace Gray
{
	TextureManager::TextureManager()
		: tl(TextureLoaderPool::GetLoader(0)),
		  nUninit(0)
	{
		tl.AddManager(*this);
	}

	TextureManager::~TextureManager()
	{
		tl.RemoveManager(*this);
	}

	WeakRef<Texture> TextureManager::GetTexture(const std::string& path)
	{
		int k = 0;
		for (const std::string& p : paths)
		{
			if (path == p)
			{
				assert(textures.size() > k);
				WeakRef<Texture> tex = textures[k];
				return tex;
			}
			k++;
		}

		NoCopy<Texture> ncTex;
		WeakRef<Texture> refTex = WeakRef<Texture>(ncTex);
		
		GRAY_CORE_INFO("Loaded " + path + " to Texture ID = " + std::to_string(ncTex->GetID()));

		toLoad.Enqueue(std::pair{refTex, path});
		textures.push_back(std::move(ncTex));
		nUninit++;

		return refTex;
	}

	bool TextureManager::RequireLoading()
	{
		return !toLoad.IsEmpty();
	}

	bool TextureManager::RequireInit()
	{
		return (nUninit != 0);
	}

	void TextureManager::InitTextures()
	{
		while(!toInit.IsEmpty())
		{
			std::pair<WeakRef<Texture>, Image> loadedImage;
			toInit.DequeueTo(loadedImage);

			auto [tex, im] = std::move(loadedImage);
			tex->LoadTextureFrom(im);
			GRAY_CORE_INFO("Initialised Texture ID = " + std::to_string(tex->GetID()));
			nUninit--;
		}
	}

}