#include "grpch.h"
#include "StaticSource.h"

namespace Gray
{
		StaticSource::StaticSource(glm::vec3 pos, glm::vec3 dir) : pos(pos), dir(dir)
		{

		}

		const glm::vec3& StaticSource::GetDir()
		{
			return dir;
		}

		const glm::vec3& StaticSource::GetPos()
		{
			return pos;
		}
}