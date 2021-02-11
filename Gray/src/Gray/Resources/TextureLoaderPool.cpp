#include "grpch.h"
#include "TextureLoaderPool.h"
#include "Gray/Window/Window.h"

namespace Gray
{
	std::vector<TextureLoader> TextureLoaderPool::pool;

	TextureLoaderPool::TextureLoaderPool()
	{
		Window::GetWindow()->AddListener(this);
		if (std::is_move_constructible<TextureLoader>::value)
		{
			pool.reserve(5);
			pool.emplace_back();
		}
	}

	TextureLoader& TextureLoaderPool::GetLoader(int n)
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