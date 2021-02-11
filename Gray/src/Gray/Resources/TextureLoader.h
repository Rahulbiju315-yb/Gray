#pragma once

#include "thread"
#include "mutex"
#include "Gray/Image/Image.h"
#include "TextureImage.h"
#include "Gray/Events/EventListener.h"

namespace Gray 
{
	class TextureManager;

	class TextureLoader
	{
	public:
		TextureLoader();
		TextureLoader(TextureLoader&&) noexcept;
		~TextureLoader();

		void AddManager(TextureManager& tm);
		void RemoveManager(TextureManager& tm);
		
	private:
		std::thread loader;
		std::vector<TextureManager*> managers;
		bool run;

		bool NextImage(std::pair<WeakRef<Texture>, std::string>& next, TextureManager& tm);
		void AddForInit(std::pair<WeakRef<Texture>, Image>& next, TextureManager& tm);

		friend void LoadFun(TextureLoader& tl);
	};
}