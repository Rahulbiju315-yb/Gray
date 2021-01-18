#pragma once

#include "Model/RenderableModel.h"

namespace Gray
{
	class RenderList
	{
	public:
		void SetCapacity(int capacity);

		RenderableModel* CreateRenderModel();
		void ClearList();

		std::vector<RenderableModel>::iterator begin();
		std::vector<RenderableModel>::iterator end();

		std::vector<RenderableModel> renderables;
	};
}