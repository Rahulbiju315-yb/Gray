#pragma once

#include "Renderable.h"

namespace Gray
{
	class RenderList
	{
	public:
		void AddRenderable(std::shared_ptr<Renderable> r);
		bool RemoveRenderable(std::shared_ptr<Renderable> r);

		std::vector<std::shared_ptr<Renderable>>::iterator begin();
		std::vector<std::shared_ptr<Renderable>>::iterator end();

		std::vector<std::shared_ptr<Renderable>> renderables;
	};
}