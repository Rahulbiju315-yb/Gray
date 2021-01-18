#include "grpch.h"
#include "RenderList.h"

namespace Gray
{
	void RenderList::SetCapacity(int capacity)
	{
		renderables.reserve(capacity);
	}

	RenderableModel* RenderList::CreateRenderModel()
	{
		renderables.push_back(RenderableModel());
		return &(renderables.back());
	}

	void RenderList::ClearList()
	{
		renderables.clear();
	}

	std::vector<RenderableModel>::iterator RenderList::begin()
	{
		return renderables.begin();
	}

	std::vector<RenderableModel>::iterator RenderList::end()
	{
		return renderables.end();
	}
}