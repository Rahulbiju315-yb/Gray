#include "grpch.h"
#include "RenderList.h"

namespace Gray
{
	void RenderList::AddRenderable(SharedRenderable r)
	{
		renderables.push_back(r);
	}

	bool RenderList::RemoveRenderable(SharedRenderable r)
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
	std::vector<SharedRenderable>::iterator RenderList::begin()
	{
		return renderables.begin();
	}
	std::vector<SharedRenderable>::iterator RenderList::end()
	{
		return renderables.end();
	}
}