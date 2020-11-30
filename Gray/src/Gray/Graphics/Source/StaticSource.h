#pragma once

#include "Source.h"
#include "glm/glm.hpp"
namespace Gray
{
	class StaticSource : public Source
	{
	public:
		StaticSource(glm::vec3 pos, glm::vec3 dir);

		virtual const glm::vec3& GetDir() override;
		virtual const glm::vec3& GetPos() override;

	private:
		glm::vec3 pos;
		glm::vec3 dir;
	};
}