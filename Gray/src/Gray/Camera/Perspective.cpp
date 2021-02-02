#include "grpch.h"
#include "Perspective.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Gray
{
	void Perspective::GetProjectionMatrix(glm::mat4& proj)
	{
		proj = glm::perspective(fov, aspectRatio, zLimNear, zLimFar);
	}
}