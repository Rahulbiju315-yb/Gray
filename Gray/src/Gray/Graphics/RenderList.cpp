#include "grpch.h"
#include "RenderList.h"

namespace Gray
{
	void RenderList::AddRenderable(std::shared_ptr<Renderable> r)
	{
		renderables.push_back(r);
	}

	bool RenderList::RemoveRenderable(std::shared_ptr<Renderable> r)
	{
		for (auto renderable : renderables)
		{
			if (renderable == r)
			{
				renderables.erase(std::remove(renderables.begin(), renderables.end(), r), renderables.end());
				return true;
			}
		}
		return false;
	}
	std::vector<std::shared_ptr<Renderable>>::iterator RenderList::begin()
	{
		return renderables.begin();
	}
	std::vector<std::shared_ptr<Renderable>>::iterator RenderList::end()
	{
		return renderables.end();
	}
}