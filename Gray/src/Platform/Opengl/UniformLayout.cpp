#include "grpch.h"
#include "UniformLayout.h"

namespace Gray
{
	uint BaseAlignOf(VarType type)
	{
		return 0;
	}

	void UniformLayout::Push(VarType type, const std::string& name)
	{
		uint baseAllign = BaseAlignOf(type);
		uint rem = allignedOffset % baseAllign;

		if(rem != 0)
			allignedOffset += baseAllign - rem;

		offsetMap.insert({ name,  allignedOffset});
		allignedOffset += baseAllign;

	}
}