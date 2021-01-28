#include "grpch.h"
#include "ResourceManager.h"

namespace Gray
{
	void FinishAllLoads()
	{
		RM_FinishModelLoad();
		RM_FinishTextureLoad();
	}
}