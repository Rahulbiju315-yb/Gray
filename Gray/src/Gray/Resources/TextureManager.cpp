#include "grpch.h"
#include "TextureManager.h"
#include "TextureLoaderPool.h"

namespace Gray
{
	std::vector<TextureManager*> TextureManager::allTM;

	TextureManager::TextureManager()
		: tl(TextureLoaderPool::GetLoader(0)),
		  nUninit(0)
	{
		tl.AddManager(*this); // store pointers not references
		allTM.push_back(this);
	}

	TextureManager::~TextureManager()
	{
		tl.RemoveManager(*this);
		allTM.erase(std::remove(allTM.begin(), allTM.end(), this), allTM.end());
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
		paths.push_back(path);
		nUninit++;
		
		tl.Notify();

		return refTex;
	}

	bool TextureManager::RequiresLoading()
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
			
			if (im.data)
				tex->LoadTextureFrom(im);
			else
				tex->LoadEmptyTexture(1, 1);

			GRAY_CORE_INFO("Initialised Texture ID = " + std::to_string(tex->GetID()));
			nUninit--;
		}
	}

	void TextureManager::InitIfRequired()
	{
		for (TextureManager* tm : allTM)
		{
			if (tm->RequireInit())
				tm->InitTextures();
		}
	}

}