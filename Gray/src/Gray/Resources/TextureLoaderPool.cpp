#include "grpch.h"
#include "TextureLoaderPool.h"
#include "Gray/Window/Window.h"

namespace Gray
{
	std::vector<TextureLoader> pool;

	TextureLoaderPool::TextureLoaderPool()
	{
		static uint id = 1;
		Window::GetWindow()->AddListener(this);

		pool.reserve(5);
		pool.emplace_back(id++);
	}

	TextureLoader& TextureLoaderPool::GetLoader(uint n)
	{
		static TextureLoaderPool tpl;
		assert(n < pool.size());
		return pool[n];
	}


	void TextureLoaderPool::OnEvent(Event& e, EventType type)
	{
		if (type == EventType::WindowClosed)
			pool.clear();
	}
}