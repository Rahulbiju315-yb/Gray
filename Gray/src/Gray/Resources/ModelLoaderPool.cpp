#include "grpch.h"
#include "ModelLoaderPool.h"
#include "Gray/Window/Window.h"

namespace Gray
{
	std::vector<ModelLoader> ModelLoaderPool::pool;

	ModelLoaderPool::ModelLoaderPool()
	{
		Window::GetWindow()->AddListener(this);
		pool.reserve(5);
		pool.emplace_back();
	}

	ModelLoader& ModelLoaderPool::GetModelLoader(int n)
	{
		static ModelLoaderPool mldr;

		assert(n < pool.size());
		return pool[n];
	}

	void ModelLoaderPool::OnEvent(Event& e, EventType type)
	{
		if (type == EventType::WindowClosed)
			pool.clear();
	}
}