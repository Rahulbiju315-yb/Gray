#pragma once
#include "Transform.h"

namespace Gray
{
	class Transformable
	{
	public:
		virtual Transform& GetTransform() = 0;
	};
}