#pragma once

#include "Renderable.h"
#include "RenderListItem.h"
namespace Gray
{
	class RenderGroup : public RenderListItem
	{
		virtual void OnUpdate(float dt) const override = 0;
	};
}