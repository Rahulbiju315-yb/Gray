#include "grpch.h"
#include "TextureLoader.h"
#include "TextureManager.h"
#include "Gray/Window/Window.h"

namespace Gray
{

	TextureLoader::TextureLoader(uint id)
		: id(id),
		  run(true)
	{
		loader = std::thread(LoadFun, std::ref(*this));
	}

	TextureLoader::TextureLoader(TextureLoader&& src) noexcept
		: loader(std::move(src.loader)),
		  managers(std::move(src.managers)),
		  run(src.run),
		  id(src.id)
	{
	}

	TextureLoader::~TextureLoader()
	{
		run = false;
		cvar.notify_one();

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

	bool TextureLoader::RequiresLoading()
	{
		for (TextureManager* tm : managers)
		{
			if (tm->RequiresLoading())
				return true;
		}

		return false;
	}

	void TextureLoader::Notify()
	{
		cvar.notify_one();
	}

	bool TextureLoader::IsRunning()
	{
		return run;
	}

	void LoadFun(TextureLoader& tl)
	{
		while (tl.run)
		{
			{
				std::unique_lock lock(tl.cvmutex);
				tl.cvar.wait(lock, [&] 
					{
						return tl.RequiresLoading() || !tl.IsRunning();
					});
			}

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