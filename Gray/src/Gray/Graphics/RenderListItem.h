#pragma once

namespace Gray
{
	class RenderListItem
	{
	public:
		virtual void OnUpdate(float dt) const = 0;
	};
}