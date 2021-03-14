#pragma once

#include "thread"
#include "mutex"
#include "Gray/Image/Image.h"
#include "Gray/Events/EventListener.h"
#include "Platform/Opengl/Texture.h"
namespace Gray 
{
	class TextureManager;

	class TextureLoader
	{
	public:
		TextureLoader(uint id);
		TextureLoader(TextureLoader&&) noexcept;
		~TextureLoader();

		void AddManager(TextureManager& tm);
		void RemoveManager(TextureManager& tm);
		bool RequiresLoading();
		void Notify();
		bool IsRunning();

	private:
		std::thread loader;
		std::vector<TextureManager*> managers;
		std::condition_variable cvar;
		std::mutex cvmutex;
	
		uint id;
		bool run;

		bool NextImage(std::pair<WeakRef<Texture>, std::string>& next, TextureManager& tm);
		void AddForInit(std::pair<WeakRef<Texture>, Image>& next, TextureManager& tm);
		friend void LoadFun(TextureLoader& tl);
	};
}