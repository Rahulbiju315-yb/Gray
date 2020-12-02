#pragma once

#include "Renderable.h"

namespace Gray
{
	class RenderList
	{
	public:
		void AddRenderable(SharedRenderable r);
		bool RemoveRenderable(SharedRenderable r);

		std::vector<SharedRenderable>::iterator begin();
		std::vector<SharedRenderable>::iterator end();

		std::vector<SharedRenderable> renderables;
	};
}