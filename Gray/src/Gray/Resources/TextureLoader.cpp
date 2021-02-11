#include "grpch.h"
#include "TextureLoader.h"
#include "TextureManager.h"
#include "Gray/Window/Window.h"

namespace Gray
{

	TextureLoader::TextureLoader()
	{
		run = true;
		loader = std::thread(LoadFun, std::ref(*this));
	}

	TextureLoader::TextureLoader(TextureLoader&& src) noexcept
		: loader(std::move(src.loader)),
		  managers(std::move(src.managers)),
		  run(src.run)
	{
	}

	TextureLoader::~TextureLoader()
	{
		run = false;
		if (loader.joinable())
			loader.join();
	}

	void TextureLoader::AddManager(TextureManager& tm)
	{
		managers.push_back(&tm);
	}

	void TextureLoader::RemoveManager(TextureManager& tm)
	{
		managers.erase(std::remove(managers.begin(), managers.end(), &tm), managers.end());
	}

	bool TextureLoader::NextImage(std::pair<WeakRef<Texture>, std::string>& next, TextureManager& tm)
	{
		if (!tm.toLoad.IsEmpty())
		{
			tm.toLoad.DequeueTo(next);
			return true;
		}

		return false;
	}

	void TextureLoader::AddForInit(std::pair<WeakRef<Texture>, Image>& loadedRes, TextureManager& tm)
	{
		tm.toInit.Enqueue(std::move(loadedRes));
	}

	void LoadFun(TextureLoader& tl)
	{
		while (tl.run)
		{
			for (TextureManager* tm : tl.managers)
			{
				std::pair<WeakRef<Texture>, std::string> nextload;
				bool available = tl.NextImage(nextload, *tm);

				if (available)
				{
					auto [tex, path] = nextload;
					
					Image loadedImage;
					LoadImage(loadedImage, path);

					tl.AddForInit(std::pair{tex, std::move(loadedImage)}, *tm);
				}
			}
		}
	}
}