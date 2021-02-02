#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Gray
{
	void RotateToVectorFrom(glm::vec3 v1, glm::vec3 v2, glm::mat4& mat);
	glm::mat4 RotationYPR(glm::vec3 yawPitchRoll);
	glm::vec3 YawPitchToXYZ(glm::vec2 yawPitch);
}